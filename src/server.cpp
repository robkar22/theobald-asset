#include "server.hpp"
#include "http.hpp"
#include "router.hpp"

#include <cstdint>
#include <cstdio>
#include <iostream>
#include <optional>
#include <string>

#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

Server::Server(std::uint16_t port) : port_(port) {}
int Server::run() {
  int server_fd = socket(AF_INET, SOCK_STREAM, 0);

  if (server_fd == -1) {

    std::cerr << "Failed to create socket \n";
    return 1;
  }

  std::cout << "Socket created: " << server_fd << '\n';

  sockaddr_in address{};

  address.sin_family = AF_INET;
  address.sin_port = htons(port_); // htons big endian
  address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

  // restart server without address-reuse dealys
  int opt = 1;
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) ==
      -1) {
    perror("setsockopt");
    close(server_fd);
    return 1;
  }

  // bind socket to address
  if (bind(server_fd, reinterpret_cast<sockaddr *>(&address),

           sizeof(address)) == -1) {
    perror("bind");
    close(server_fd);
    return -1;
  }
  // listen
  if (listen(server_fd, 10) == -1) {

    perror("listen");
    close(server_fd);
    return 1;
  }

  std::cout << "socket bound to 127.0.0.1:8080\n";

  while (true) {
    int client_fd = accept(server_fd, nullptr, nullptr);
    if (client_fd == -1) {
      perror("accept");
      close(server_fd);
      return 1;
    }
    char buffer[4096]{};
    ssize_t bytes_received = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
    if (bytes_received > 0) {
      buffer[bytes_received] = '\0';
      std::cout << buffer << '\n';

    } else if (bytes_received == 0) {
      std::cout << "client disconnected\n";

    } else {
      perror("recv");
    }
    if (bytes_received <= 0) {
      if (bytes_received == -1)
        perror("recv");
      close(client_fd);
      continue;
    }
    std::string raw_request(buffer, bytes_received);
    std::optional<HttpRequest> request = parse_http_request(raw_request);
    if (!request) {
      std::cout << "parising failed!\n";
    }
    HttpResponse response;
    if (request.has_value()) {
      response = handle_request(*request);
    } else {
      response.body = "Bad Request";
      response.status = 400;
    }

    std::string http_message = build_http_response(response);

    ssize_t bytes_sent =
        send(client_fd, http_message.data(), http_message.size(), 0);
    if (bytes_sent == -1) {
      perror("send");
    } else {
      std::cout << "sent " << bytes_sent << " bytes\n";
    }

    close(client_fd);
  }
  return 0;
}
