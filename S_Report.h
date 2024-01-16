#pragma once
#ifndef S_REPORT_H
#define S_REPORT_H

#include <string>
#include <vector>
#include "S_DBConnection.h"

class S_Report
{
public:
	int PackageID, StaffID, Reserved, ReservationReviewed;
	double AverageRate;

	S_Report(sql::ResultSet* data);

	static std::vector<S_Report> summary(int month, int year);

	~S_Report(){}
};

#endif