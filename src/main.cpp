#include "database.hpp"
#include "server.hpp"


int main() {
Database db("theobald.db");
  Server server(8080);
  return server.run();

  }


