#pragma once
#ifndef S_RESERVATION_H
#define S_RESERVATION_H

#include <string>
#include <vector>
#include "S_Package.h"
#include "S_DBConnection.h";

class S_Reservation
{
public:

	int CustomerID, ReservationID, PackageID, R_Extra;
	std::string R_Tool, R_Date, R_Time, R_Description;
	double R_Total;
	bool tool;

	S_Package items1;

	S_Reservation();
	S_Reservation(sql::ResultSet* data);
	void addreservation();
	void cancel();
	void addpackage(S_Package package);
	double totalreservation();

	static S_Reservation findReservation(int CustomerID, int ReservationID);
	static std::vector<S_Reservation> viewreservations(int CustomerID);

	~S_Reservation() {}
};

#endif