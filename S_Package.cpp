#include "S_Package.h"
#include <vector>

using namespace std;

S_Package::S_Package() 
{
	PackageID = 0;
	P_Name = "";
	P_Price = 0;
	P_Detail = "";
	P_Hour = 0;
	P_CleanerAmount = 0;
	StaffID = 0;
}

S_Package::S_Package(sql::ResultSet* data) 
{
	PackageID = data->getInt("PackageID");
	P_Name = data->getString("P_Name");
	P_Price = data->getDouble("P_Price");
	P_Detail = data->getString("P_Detail");
	P_Hour = data->getInt("P_Hour");
	P_CleanerAmount = data->getInt("P_CleanerAmount");
	StaffID = data->getInt("StaffID");
}

void S_Package::insert()
{
	S_DBConnection DB;
	DB.prepareStatement("Insert into package (P_Name,P_Price,P_Detail,P_Hour,StaffID) VALUES (?,?,?,?,?)");
	DB.stmt->setString(1, P_Name);
	DB.stmt->setDouble(2, P_Price);
	DB.stmt->setString(3, P_Detail);
	DB.stmt->setInt(4, P_Hour);
	DB.stmt->setInt(5, StaffID);
	DB.QueryStatement();
	DB.~S_DBConnection();
}

vector<S_Package> S_Package::findPackage() 
{
	string query = "SELECT * FROM package ORDER BY PackageID";

	query += " ASC";
	 
	S_DBConnection DB;
	DB.prepareStatement(query);

	vector<S_Package> package;

	DB.QueryResult();

	if (DB.res->rowsCount() > 0) 
	{
		while (DB.res->next()) 
		{
			S_Package tmpPackage(DB.res);
			package.push_back(tmpPackage);
		}
	}

	DB.~S_DBConnection();
	return package;
}

S_Package S_Package::findPackage(int PackageID) 
{
	S_DBConnection DB;
	DB.prepareStatement("SELECT * FROM package WHERE PackageID=?");
	DB.stmt->setInt(1, PackageID);
	DB.QueryResult();

	S_Package result;
	if (DB.res->rowsCount() == 1) 
	{
		while (DB.res->next()) {
			S_Package found(DB.res);
			result = found;
		}
	}
	
	DB.~S_DBConnection();
	return result;
}

S_Package::~S_Package() {}