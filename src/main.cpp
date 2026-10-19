#include "database.hpp"
#include <iostream>
#include "server.hpp"


int main() {
Database db("theobald.db");
  if(db.create_tables()){
    if(db.add_person("roberth"))
      std::cout << "Person added successfully\n";
  }

  Server server(8080);
  return server.run();

  }


