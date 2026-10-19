#pragma once

#include <sqlite3.h>
#include <string>
#include <vector>
struct Person {

  int id;
  std::string name;
};

class Database {
public:
  explicit Database(const char *filename);
  ~Database();
  bool create_tables();
  bool add_person(const std::string &name);
  std::vector<Person> get_people();

private:
  sqlite3 *db_ = nullptr;
};
