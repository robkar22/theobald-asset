#pragma once

#include <cstdint>

class Server {
public:
  explicit Server(std::uint16_t port);
  int run();

private:
  std::uint16_t port_;
};
