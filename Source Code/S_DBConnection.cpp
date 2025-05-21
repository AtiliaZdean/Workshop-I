#include "S_DBConnection.h"
#include <conio.h>

using namespace std;
using namespace sql;

S_DBConnection::S_DBConnection() {

	try {
		mysql::MySQL_Driver* driver = mysql::get_mysql_driver_instance();

		connection = driver->connect("tcp://127.0.0.1:3306", "root", "");
		//database address, username, password

		connection->setSchema("cleaning_service"); //database name
		stmt = nullptr;
		res = nullptr;
	}
	catch (sql::SQLException& e) {
		if (e.getErrorCode() == 0) {
			system("cls");
			cout << "Unable to connect to database";
			_getch();
			exit(0);
			return;
		}
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
		_getch();
	}
}



S_DBConnection::~S_DBConnection() {
	try {
		if (connection) {
			connection->close();
		}
		if (stmt) {
			stmt->close();
		}
		if (res) {
			res->close();
		}
	}
	catch (sql::SQLException& e) {
		if (e.getErrorCode() != 0) {
			cout << "# ERR: SQLException in " << __FILE__;
			cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
			cout << "# ERR: " << e.what();
			cout << " (MySQL error code: " << e.getErrorCode();
			cout << ", SQLState: " << e.getSQLState() << " )" << endl;
			_getch();
		}
	}
}

void S_DBConnection::prepareStatement(string query) {
	stmt = connection->prepareStatement(query);
}

void S_DBConnection::QueryStatement() {

	try {
		stmt->executeUpdate();
	}
	catch (sql::SQLException& e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
		_getch();
	}
}

void S_DBConnection::QueryResult() {

	try {
		res = stmt->executeQuery();
	}
	catch (sql::SQLException& e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
		_getch();
	}
}

int S_DBConnection::getGeneratedId() {
	prepareStatement("SELECT LAST_INSERT_ID();");
	QueryResult();
	int lastInsertId = -1;
	if (res->rowsCount() > 0) {
		while (res->next()) {
			lastInsertId = res->getInt64("LAST_INSERT_ID()");
		}
	}
	return lastInsertId;
}