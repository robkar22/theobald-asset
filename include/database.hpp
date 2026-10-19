#pragma once

#include <string>
#include <sqlite3.h>

class Database {
public:
	explicit Database(const char* filename);
	~Database();
	bool create_tables();
	bool add_person(const std::string &name);
	

private:
	sqlite3* db_ = nullptr;


};
