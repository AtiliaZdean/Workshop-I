#include "S_Staff.h"
#include "S_DBConnection.h"
using namespace std;

S_Staff::S_Staff()
{
	StaffID = 0;
	S_Name = "";
	S_Contact = "";
	S_Email = "";
	S_Password = "";
}

S_Staff::S_Staff(int StaffID, std::string S_Name, std::string S_Contact, std::string S_Email, std::string S_Password)
{
	this->StaffID = StaffID;
	this->S_Name = S_Name;
	this->S_Contact = S_Contact;
	this->S_Email = S_Email;
	this->S_Password = S_Password;
}

bool S_Staff::login()
{
	S_DBConnection DB;
	DB.prepareStatement("SELECT * FROM staff WHERE S_Email=? AND S_Password=?");
	DB.stmt->setString(1, S_Email);
	DB.stmt->setString(2, S_Password);
	DB.QueryResult();
	if (DB.res->rowsCount() == 1) {
		while (DB.res->next()) {
			StaffID = DB.res->getInt("StaffID");
			S_Name = DB.res->getString("S_Name");
			S_Contact = DB.res->getString("S_Contact");
			S_Email = DB.res->getString("S_Email");
			S_Password = DB.res->getString("S_Password");
		}
		DB.~S_DBConnection();
		return true;
	}
	else {

		DB.~S_DBConnection();
		return false;
	}
}

void S_Staff::insert()
{
	S_DBConnection DB;
	DB.prepareStatement("Insert into staff (S_Name,S_Contact,S_Email,S_Password) VALUES (?,?,?,?)");
	DB.stmt->setString(1, S_Name);
	DB.stmt->setString(2, S_Contact);
	DB.stmt->setString(3, S_Email);
	DB.stmt->setString(4, S_Password);
	DB.QueryStatement();
	DB.~S_DBConnection();
}

S_Staff::~S_Staff() {}