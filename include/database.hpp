#pragma once


#include <sqlite3.h>

class Database {
public:
	explicit Database(const char* filename);
	~Database();
	bool create_tables();
	

private:
	sqlite3* db_ = nullptr;


};
