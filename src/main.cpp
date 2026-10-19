#include "database.hpp"
#include "router.hpp"
#include "server.hpp"
#include <iostream>

int main() {
  Database db("theobald.db");
  if (!db.create_tables()) {
    return 1;
  }
  std::cout << escape_json("Robert \"Bob\"") << '\n';

  Server server(8080,db);
  return server.run();
}
