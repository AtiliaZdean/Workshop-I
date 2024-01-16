#pragma once
#ifndef S_STAFF_H
#define S_STAFF_H

#include <string>
#include <vector>

class S_Staff
{
public:
	std::string S_Name, S_Contact, S_Email, S_Password;
	int StaffID;

	S_Staff();
	S_Staff(int StaffID, std::string S_Name, std::string S_Contact, std::string S_Email, std::string S_Password);
	bool login();
	void insert();
	~S_Staff();
};

#endif