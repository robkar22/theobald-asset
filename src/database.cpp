#include <database.hpp>
#include <iostream>
#include <sqlite3.h>

Database::Database(const char *filename) {
  int db = sqlite3_open(filename, &db_);

  if (db == SQLITE_OK) {

    std::cout << "Database opend\n";
  } else {
    std::cerr << "Failed to open database: " << sqlite3_errmsg(db_) << '\n';
  }
}

Database::~Database() { sqlite3_close(db_); }

bool Database::create_tables() {
  const char *sql = R"(
	CREATE TABLE IF NOT EXISTS people (
	id INTEGER PRIMARY KEY,
	name TEXT NOT NULL
	);
	)";

        if (sqlite3_exec(db_, sql, nullptr, nullptr, nullptr) == SQLITE_OK){
    return true;

	}else{
    std::cerr << sqlite3_errmsg(db_);
    return false;

	};
}
