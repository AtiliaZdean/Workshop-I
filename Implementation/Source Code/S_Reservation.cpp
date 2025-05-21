#include "S_Reservation.h"
#include <string> 
#include <vector>

#define extraprice 25
#define toolprice 55

using namespace std;

S_Reservation::S_Reservation()
{
	CustomerID = 0;
	ReservationID = 0;
	R_Extra = 0;
	R_Tool = "No";
	R_Date = "";
	R_Time = "";
	R_Description = "";
	R_Total = 0;
	tool = false;
}

S_Reservation::S_Reservation(sql::ResultSet* data)
{
	ReservationID = data->getInt("ReservationID");
	CustomerID = data->getInt("CustomerID");
	PackageID = data->getInt("PackageID");
	R_Extra = data->getInt("R_Extra");
	R_Tool = data->getString("R_Tool");
	R_Date = data->getString("R_Date");
	R_Time = data->getString("R_Time");
	R_Description = data->getString("R_Description");
	R_Total = data->getDouble("R_Total");
}

void S_Reservation::addreservation()
{
	S_DBConnection DB;

	DB.prepareStatement("INSERT INTO reservation(CustomerID, PackageID, R_Extra, R_Tool, R_Date, R_Time, R_Description, R_Total) VALUES (?, ?, ?, ?, ?, STR_TO_DATE(?,'%T'), ?, ?)");

	DB.stmt->setInt(1, CustomerID);
	DB.stmt->setInt(2, items1.PackageID);
	DB.stmt->setInt(3, R_Extra);
	DB.stmt->setString(4, R_Tool);
	DB.stmt->setString(5, R_Date); 
	DB.stmt->setString(6, R_Time);
	DB.stmt->setString(7, R_Description);
	DB.stmt->setDouble(8, R_Total);

	DB.QueryStatement();

	DB.~S_DBConnection();
}

vector<S_Reservation> S_Reservation::viewreservations(int CustomerID)
{
	S_DBConnection DB;

	DB.prepareStatement("SELECT * FROM reservation WHERE CustomerID = ?");
	DB.stmt->setInt(1, CustomerID);

	vector<S_Reservation> reservation;

	DB.QueryResult();

	if (DB.res->rowsCount() > 0) 
	{
		while (DB.res->next())
		{
			S_Reservation tmpReservation(DB.res);
			reservation.push_back(tmpReservation);
		}
	}

	DB.~S_DBConnection();
	return reservation;
}

S_Reservation S_Reservation::findReservation(int CustomerID, int ReservationID)
{
	S_DBConnection DB;
	DB.prepareStatement("SELECT * FROM reservation WHERE CustomerID = ? AND ReservationID = ?");
	DB.stmt->setInt(1, CustomerID);
	DB.stmt->setInt(2, ReservationID);
	DB.QueryResult();

	S_Reservation result;
	if (DB.res->rowsCount() == 1) 
	{
		while (DB.res->next()) {
			S_Reservation found(DB.res);
			result = found;
		}
	}

	DB.~S_DBConnection();
	return result;
}

void S_Reservation::addpackage(S_Package package)
{
	items1 = package;
}

double S_Reservation::totalreservation()
{
	double total = 0;

	total += items1.P_Price;

	total += items1.P_Hour * (extraprice * R_Extra);

	if (tool)
	{
		total += toolprice;
	}

	total += total * 0.06;  //SST 6%

	return total;
}