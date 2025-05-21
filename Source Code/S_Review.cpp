#include "S_Review.h"

using namespace std;

S_Review::S_Review()
{
	ReviewID = 0;
	ReservationID = 0;
	R_Rate = 0;
	R_Comment = "";
}

S_Review::S_Review(sql::ResultSet* data)
{
	R_Rate = data->getDouble("R_Rate");
	R_Comment = data->getString("R_Comment");
	PackageID = data->getInt("PackageID");
	C_FirstName = data->getString("C_FirstName");
}

void S_Review::addreview()
{
	S_DBConnection DB;

	DB.prepareStatement("INSERT INTO review (ReservationID, R_Rate, R_Comment) VALUES (?, ?, ?)");

	DB.stmt->setInt(1, ReservationID);
	DB.stmt->setDouble(2, R_Rate);
	DB.stmt->setString(3, R_Comment);

	DB.QueryStatement();

	DB.~S_DBConnection();
}

vector<S_Review> S_Review::viewreview()
{
	S_DBConnection DB;

	DB.prepareStatement("SELECT v.R_Rate AS R_Rate, v.R_Comment AS R_Comment, s.PackageID AS PackageID, c.C_FirstName AS C_FirstName "
		                "FROM review v "
		                "JOIN reservation s ON v.ReservationID = s.ReservationID " 
		                "JOIN customer c ON c.CustomerID = s.CustomerID "
		                "ORDER BY v.R_Rate ASC");

	vector<S_Review> review;

	DB.QueryResult();

	if (DB.res->rowsCount() > 0)
	{
		while (DB.res->next())
		{
			S_Review tmpReservation(DB.res);
			review.push_back(tmpReservation);
		}
	}

	DB.~S_DBConnection();
	return review;
}

vector<S_Review> S_Review::findReview(int PackageID)
{
	S_DBConnection DB;

	DB.prepareStatement("SELECT v.R_Rate AS R_Rate, v.R_Comment AS R_Comment, s.PackageID AS PackageID, c.C_FirstName AS C_FirstName "
		"FROM review v "
		"JOIN reservation s ON v.ReservationID = s.ReservationID "
		"JOIN customer c ON c.CustomerID = s.CustomerID "
		"WHERE s.PackageID = ? "
		"ORDER BY v.R_Rate ASC");

	DB.stmt->setInt(1, PackageID);

	vector<S_Review> review;

	DB.QueryResult();

	if (DB.res->rowsCount() > 0)
	{
		while (DB.res->next())
		{
			S_Review tmpReservation(DB.res);
			review.push_back(tmpReservation);
		}
	}

	DB.~S_DBConnection();
	return review;
}