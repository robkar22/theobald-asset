#include "http.hpp"
#include <optional>

std::string build_http_response(const HttpResponse &response) {

  std::string reason;

  switch (response.status) {
  case 200:
    reason = "OK";
    break;
  case 404:
    reason = "Not Found";
    break;
  case 400:
    reason = "Bad Request";
    break;
  default:
    reason = "Internal Server Error";
  }
  std::string result =
      "HTTP/1.1 " + std::to_string(response.status) + " " + reason + "\r\n" +
      "Content-Type: " + response.content_type + "\r\n" +
      "Content-Length: " + std::to_string(response.body.size()) + "\r\n" +
      "Connection: close\r\n" + "\r\n" + response.body;

  return result;
}

std::optional<HttpRequest> parse_http_request(const std::string &raw_request) {

  HttpRequest http_request{};
  size_t pos = raw_request.find("\r\n");
  if (pos == std::string::npos) {
    return std::nullopt;
  }

  std::string request_line = raw_request.substr(0, pos);
  size_t first_space = request_line.find(' ');
  if (first_space == std::string::npos) {
    return std::nullopt;
  }
  size_t second_space = request_line.find(' ', first_space + 1);
  if (second_space == std::string::npos) {
    return std::nullopt;
  }
  size_t header_separator = raw_request.find("\r\n\r\n");
  if(header_separator == std::string::npos){
    return std::nullopt;
  }
  http_request.method = request_line.substr(0, first_space);

  http_request.path =
      request_line.substr(first_space + 1, second_space - first_space - 1);

  http_request.version = request_line.substr(second_space + 1);
  http_request.body = raw_request.substr(header_separator + 4);

  if (http_request.version.empty() || http_request.method.empty() ||
      http_request.path.empty()) {
    return std::nullopt;
  }
  return http_request;
}
