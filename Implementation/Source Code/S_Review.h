#pragma once
#ifndef S_REVIEW_H
#define S_REVIEW_H

#include <string>
#include <vector>
#include "S_DBConnection.h";

class S_Review
{
public:

	int ReviewID, ReservationID, PackageID;
	double R_Rate;
	std::string R_Comment, C_FirstName;

	S_Review();
	S_Review(sql::ResultSet* data);

	void addreview();

	static std::vector<S_Review> viewreview();
	static std::vector<S_Review> findReview(int PackageID);

	~S_Review(){}
};
#endif