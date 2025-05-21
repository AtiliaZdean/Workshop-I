#include "S_Account.h"
#include "S_DBConnection.h"
using namespace std;

S_Account::S_Account()
{
	CustomerID = 0;
	C_FirstName = "";
	C_LastName = "";
	C_Address = "";
	C_PostCode = 0;
	C_City = "";
	C_State = "";
	C_Contact = "";
	C_Email = "";
	C_Password = "";
}

S_Account::S_Account(int CustomerID, std::string C_FirstName, std::string C_LastName, std::string C_Address, int C_PostCode, std::string C_City, std::string C_State, std::string C_Contact, std::string C_Email, std::string C_Password)
{
	this->CustomerID = CustomerID;
	this->C_FirstName = C_FirstName;
	this->C_LastName = C_LastName;
	this->C_Address = C_Address;
	this->C_PostCode = C_PostCode;
	this->C_City = C_City;
	this->C_State = C_State;
	this->C_Contact = C_Contact;
	this->C_Email = C_Email;
	this->C_Password = C_Password;
}

bool S_Account::login()
{
	S_DBConnection DB;
	DB.prepareStatement("SELECT * FROM customer WHERE C_Email=? AND C_Password=?");
	DB.stmt->setString(1, C_Email);
	DB.stmt->setString(2, C_Password);
	DB.QueryResult();
	if (DB.res->rowsCount() == 1) {
		while (DB.res->next()) {
			CustomerID = DB.res->getInt("CustomerID");
			C_FirstName = DB.res->getString("C_FirstName");
			C_LastName = DB.res->getString("C_LastName");
			C_Address = DB.res->getString("C_Address");
			C_PostCode = DB.res->getInt("C_PostCode");
			C_City = DB.res->getString("C_City");
			C_State = DB.res->getString("C_State");
			C_Contact = DB.res->getString("C_Contact");
			C_Email = DB.res->getString("C_Email");
			C_Password = DB.res->getString("C_Password");
		}
		DB.~S_DBConnection();
		return true;
	}
	else {

		DB.~S_DBConnection();
		return false;
	}
}

void S_Account::insert()
{
	S_DBConnection DB;
	DB.prepareStatement("Insert into customer (C_FirstName,C_LastName,C_Address,C_PostCode,C_City,C_State,C_Contact,C_Email,C_Password) VALUES (?,?,?,?,?,?,?,?,?)");
	DB.stmt->setString(1, C_FirstName);
	DB.stmt->setString(2, C_LastName);
	DB.stmt->setString(3, C_Address);
	DB.stmt->setInt(4, C_PostCode);
	DB.stmt->setString(5, C_City);
	DB.stmt->setString(6, C_State);
	DB.stmt->setString(7, C_Contact);
	DB.stmt->setString(8, C_Email);
	DB.stmt->setString(9, C_Password);
	DB.QueryStatement();
	DB.~S_DBConnection();
}

void S_Account::update() 
{
	S_DBConnection DB;
	DB.prepareStatement("UPDATE customer SET C_FirstName = ?, C_LastName = ?, C_Address = ?, C_PostCode = ?, C_City = ?, C_State = ?, C_Contact = ?, C_Password = ? WHERE CustomerID = ?");
	DB.stmt->setString(1, C_FirstName);
	DB.stmt->setString(2, C_LastName);
	DB.stmt->setString(3, C_Address);
	DB.stmt->setInt(4, C_PostCode);
	DB.stmt->setString(5, C_City);
	DB.stmt->setString(6, C_State);
	DB.stmt->setString(7, C_Contact);
	DB.stmt->setString(8, C_Password);
	DB.stmt->setInt(9, CustomerID);
	DB.QueryStatement();
	DB.~S_DBConnection();
}

void S_Account::remove()
{
	S_DBConnection DB;
	DB.prepareStatement("DELETE FROM customer WHERE CustomerID = ?");
	DB.stmt->setInt(1, CustomerID);
	DB.QueryStatement();
	DB.~S_DBConnection();
}

bool S_Account::findAccount(std::string C_Email)
{
	S_DBConnection DB;
	DB.prepareStatement("SELECT * FROM customer WHERE C_Email = ?");
	DB.stmt->setString(1, C_Email);
	DB.QueryResult();

	S_Account result;
	if (DB.res->rowsCount() == 1) 
	{
		while (DB.res->next()) 
		{
			DB.res->getString("C_Email");
		}
		DB.~S_DBConnection();
		return true;
	}
	else 
	{
		DB.~S_DBConnection();
		return false;
	}
}

S_Account::~S_Account() {}