#pragma once
#ifndef S_DBConnection_H
#define S_DBConnection_H
#include <mysql/jdbc.h>
#include <string>
class S_DBConnection
{

public:
	S_DBConnection();
	~S_DBConnection();
	void prepareStatement(std::string query);
	sql::PreparedStatement* stmt;
	sql::ResultSet* res;
	void QueryStatement(); // have no result
	void QueryResult(); // it has result
	int getGeneratedId();

private:
	sql::Connection* connection;

};

#endif