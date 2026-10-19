#include <database.hpp>
#include <iostream>
#include <sqlite3.h>

Database::Database(const char *filename) {
  int result = sqlite3_open(filename, &db_);

  if (result == SQLITE_OK) {

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

  if (sqlite3_exec(db_, sql, nullptr, nullptr, nullptr) == SQLITE_OK) {
    return true;

  } else {
    std::cerr << sqlite3_errmsg(db_);
    return false;
  };
}

bool Database::add_person(const std::string &name) {
  const char *sql = "INSERT INTO people (name) VALUES (?);";

  sqlite3_stmt *stmt = nullptr;
  int result = sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);

  if (result != SQLITE_OK) {
    std::cerr << sqlite3_errmsg(db_) << '\n';
    return false;
  }
  std::cout << "statement prepared\n";
  result = sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);
  if (result != SQLITE_OK) {
    std::cerr << sqlite3_errmsg(db_) << '\n';
    sqlite3_finalize(stmt);
    return false;
  }

  result = sqlite3_step(stmt);
  bool success = (result == SQLITE_DONE);

  if (!success) {
    std::cerr << sqlite3_errmsg(db_) << '\n';
  }

  sqlite3_finalize(stmt);

  return success;
}
