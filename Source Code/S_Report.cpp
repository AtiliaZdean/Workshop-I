#include "S_Report.h"
using namespace std;
using namespace sql;

S_Report::S_Report(ResultSet* data)
{
	PackageID = data->getInt("PackageID");
	StaffID = data->getInt("StaffID"); 
	Reserved = data->findColumn("Reserved") != 0 ? data->getInt("Reserved") : 0;
	ReservationReviewed = data->findColumn("ReservationReviewed") != 0 ? data->getInt("ReservationReviewed") : 0;
	AverageRate = data->findColumn("AverageRate") != 0 ? data->getDouble("AverageRate") : 0.0;
}

vector<S_Report> S_Report::summary(int month, int year)
{
	S_DBConnection DB;

	DB.prepareStatement("SELECT s.PackageID AS PackageID, p.StaffID AS StaffID, COUNT(s.ReservationID) AS Reserved, COUNT(v.ReservationID) AS ReservationReviewed, AVG(v.R_Rate) AS AverageRate "
		"FROM package p "
		"LEFT JOIN reservation s ON p.PackageID = s.PackageID "
		"LEFT JOIN review v ON v.ReservationID = s.ReservationID "
		"WHERE s.R_Date LIKE ? "
		"GROUP BY p.PackageID "
		"ORDER BY AVG(v.R_Rate) IS NULL, AVG(v.R_Rate) DESC");

	DB.stmt->setString(1, "%" + to_string(month) + "-" + to_string(year));

	vector <S_Report> summary;

	DB.QueryResult(); 

	if (DB.res->rowsCount() > 0) 
	{
		while (DB.res->next()) 
		{
			S_Report tmpReservation(DB.res); 
			summary.push_back(tmpReservation); 
		}
	}

	DB.~S_DBConnection();
	return summary;
}