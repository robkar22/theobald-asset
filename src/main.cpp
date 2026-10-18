#include "database.hpp"
#include <iostream>
#include "server.hpp"


int main() {
Database db("theobald.db");
  if(db.create_tables()){
    std::cout << "Tables created successfully\n";

  }
  Server server(8080);
  return server.run();

  }


