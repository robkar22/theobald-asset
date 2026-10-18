#include <database.hpp>
#include <iostream>
#include <sqlite3.h>

Database::Database(const char *filename) {
  int db = sqlite3_open(filename, &db_);

  if (db == SQLITE_OK) {

    std::cout << "Database opend";
  } else {
    std::cerr << "Failed to open database: " << sqlite3_errmsg(db_) << '\n';
  }
}

Database::~Database() { sqlite3_close(db_); }
