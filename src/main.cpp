#include "database.hpp"
#include "server.hpp"
#include <iostream>
#include <vector>

int main() {
  Database db("theobald.db");
  if (db.create_tables()) {
    if (db.add_person("roberth"))
      std::cout << "Person added successfully\n";
    std::vector<Person> people = db.get_people();
    std::cout << "people found: " << people.size() << '\n';
    for (const Person &p : people) {
      std::cout << p.id << ": " << p.name << '\n';
    }
  }

  Server server(8080);
  return server.run();
}
