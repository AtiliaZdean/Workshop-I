#pragma once
#ifndef S_ACCOUNT_H
#define S_ACCOUNT_H

#include <string>
//#include <vector>

class S_Account
{
public:
	std::string C_FirstName, C_LastName, C_Address, C_City, C_State, C_Contact, C_Email, C_Password;
	int CustomerID, C_PostCode;

	S_Account();
	S_Account(int CustomerID, std::string C_FirstName, std::string C_LastName, std::string C_Address, int C_PostCode, std::string C_City, std::string C_State, std::string C_Contact, std::string C_Email, std::string C_Password);
	bool login();
	void insert();
	void update();
	void remove();
	~S_Account();

	bool findAccount(std::string C_Email);
};

#endif