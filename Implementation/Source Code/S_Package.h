#pragma once
#ifndef S_PACKAGE_H
#define S_PACKAGE_H

#include <string>
#include <vector>
#include "S_DBConnection.h"

class S_Package
{
public:
	int PackageID, P_Hour, P_CleanerAmount, StaffID;
	std::string P_Name, P_Detail;
	double P_Price;

	S_Package();
	S_Package(sql::ResultSet* data);

	void insert();

	~S_Package();

	static S_Package findPackage(int PackageID);
	static std::vector<S_Package> findPackage();
};

#endif