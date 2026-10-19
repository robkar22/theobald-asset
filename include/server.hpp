#pragma once

#include "database.hpp"
#include <cstdint>

class Server {
public:
  explicit Server(std::uint16_t port,Database& db);
  int run();

private:
  std::uint16_t port_;
  Database& db_;
};
