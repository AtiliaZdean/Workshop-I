#include <iostream>
#include <conio.h>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <string>

#include "S_Account.h"
#include "S_Staff.h"
#include "S_Menu.h"
#include "S_Reservation.h"
#include "S_Package.h"
#include "S_Review.h"
#include "S_Report.h"
using namespace std;

void mainhome();

//staff
void sregistration();
void slogin();
void shome(S_Staff SS);
void newpackage(S_Staff SS);
void viewsummary();

//customer
void cregistration();
void clogin();
void chome(S_Account SA);
S_Account cedit(S_Account SA);
void feedback(S_Account SA);
void RAction(S_Account SA);
void reservation(S_Account SA);
void view(S_Account SA);

S_Reservation package(S_Account SA, S_Reservation SR);
S_Reservation findpackage(S_Account SA, int id, S_Reservation SR);
string hidepwd(string pwd);
bool checkdate(const string& dateinput);

int id, day, month, year;

int main()
{
	while(1) 
	{
		bool loop = true;
		char signin;

		system("cls");
		mainhome();
		
		cout << "\n\t\t\tSign-In/Register [C - Customer | S - Staff | X - exit] : ";
		cin >> signin;

		S_Menu menu;
		menu.addOption("    Registration    ");
		menu.addOption("       Login        ");
		menu.addOption("        Back        ");

		if (signin == 'C' || signin == 'c')
		{
			menu.header = "      Customer     ";

			while (loop)
			{
				switch (menu.prompt2())
				{
				case -1:
					return 0;
					break;
				case 0:
					cregistration();  //to register new customer
					break;
				case 1:
					clogin();  //existing customer login
					break;
				case 2:
					loop = false; break;
				default: break;
				}
			}
		}
		else if (signin == 'S' || signin == 's')
		{
			menu.header = "        Staff      ";

			while (loop)
			{
				switch (menu.prompt2())
				{
				case -1:
					return 0;
					break;
				case 0:
					sregistration();  //to register new staff
					break;
				case 1:
					slogin();  //existing staff login
					break;
				case 2:
					loop = false; break;
				default: break;
				}
			}
		}
		else
			return 0;
	}
}

void mainhome()  //displaying home page: welcome message, packages available, information about service
{
	vector<S_Package> package;

	cout << "\t\t\t\t\t\t\t\t\t " << char(201);      for (int i = 0; i < 41; i++) { cout << char(205); }      cout << char(187) << endl;
	cout << "\t\t\t\t\t\t\t\t\t " << char(42) << "                                         " << char(42) << endl;
	cout << "\t\t\t\t\t\t\t\t\t " << char(42) << "  ELLACENT RESIDENTIAL CLEANING SERVICE  " << char(42) << endl;
	cout << "\t\t\t\t\t\t\t\t\t " << char(42) << "                                         " << char(42) << endl;
	cout << "\t\t\t\t\t\t\t\t\t " << char(200);      for (int i = 0; i < 41; i++) { cout << char(205); }      cout << char(188) << endl << endl;

	cout << "\t\t\t\t\t\t\tWelcome to EllaCent Residential Cleaning Service! We are extremely happy to" << endl;
	cout << "\t\t\t\t\t\t\tserve you, with the utmost professionalism, reliability, and respect. It is" << endl;
	cout << "\t\t\t\t\t\t\t\tour mission to serve and make the lives of our clients easier." << endl;
	cout << "\n\t\t\t\t\t\t\t\t\t    !! ENJOY OUR NEW YEAR'S 10% DEAL !!" << endl << endl;
	
	package = S_Package::findPackage();  //find all available packages to display
    cout << "\n\t\t\t\t\t\t\t\t\t\t\t* Packages Available * \n\n";
    cout << "\t\t\t*" << setw(3) << "ID" << setw(2) << "*" << setw(15) << "Name" << setw(4) << "*" << setw(11) << "Price (RM)" << setw(2) << "*" << setw(75) << "Detail" << setw(2) << "*" << setw(9) << "Duration" << setw(2) << "*" << setw(15) << "Cleaner Amount" << setw(2) << "*";
	cout << "\n\t\t\t***********************************************************************************************************************************************";
	for (int i = 0; i < package.size(); i++)
	{
		cout << "\n\t\t\t*" << setw(3) << package[i].PackageID << setw(2) << "*" << setw(15) << package[i].P_Name << setw(4) << "*" << setw(11) << fixed << setprecision(2) << package[i].P_Price << setw(2) << "*" << setw(75) << package[i].P_Detail << setw(2) << "*" << setw(9) << package[i].P_Hour << setw(2) << "*" << setw(15) << package[i].P_CleanerAmount << setw(2) << "*" << endl;
	}

	cout << "\n\t\t\t*Cleaning tools are not included in the package but can be added in the reservation.\n\t\t\t*Each package included 2 cleaners.\n\t\t\t*Goods and services are subject to 6 % SST and the price above is exclusive of SST." << endl;

	cout << "\n\t\t\tWorking Days : Monday - Sunday" << endl;
	cout << "\n\t\t\tAny question about reservation or modification for your reservation, please contact below" << endl;
	cout << "\n\t\t\tContact : 012-3456789 \t\t\tEmail : ellacent@gmail.com" << endl;
}

void sregistration()  //registering new staff
{
	S_Menu menu;
	menu.header = "    Registration   ";
	menu.addOption("        Name*       ");
	menu.addOption("       Contact*     ");
	menu.addOption("        Email*      ");
	menu.addOption("       Password*    ");
	menu.addOption("       Register*    ");
	menu.addOption("         Back       ");
	menu.footer = "* - mandatory";

	S_Staff SS;
	int option = 0;
	string tmp;

	while (1)
	{
		option = menu.prompt1(option);
		switch (option)
		{
		case -1:
			return;
			break;
		case 0:
			cout << "\n\t\t\t\t\t\t\t\tName " << char(175) << " ";
			cin >> SS.S_Name;
			menu.setValue(0, SS.S_Name);  //to display user's input
			break;
		case 1:
			cout << "\n\t\t\t\t\t\t\t\tContact " << char(175) << " ";
			cin >> SS.S_Contact;
			menu.setValue(1, SS.S_Contact);
			break;
		case 2:
			cout << "\n\t\t\t\t\t\t\t\tEmail " << char(175) << " ";
			cin >> SS.S_Email;
			menu.setValue(2, SS.S_Email);
			break;
		case 3:  //to do: make sure that password is accepted
			do
			{
				cout << "\n\t\t\t\t\t\t\t\tPassword " << char(175) << " ";
				cin >> tmp;

				if (tmp.length() > 5 && tmp.length() < 13)  //make sure that password length is more than 5 digits and lest than 13 digits
				{
					SS.S_Password = tmp;
					menu.setValue(3, SS.S_Password);
				}
				else
					cout << "\n\t\t!!Password must be 6 to 12 character!!" << endl;

			} while (tmp.length() <= 5 || tmp.length() >= 13);
			break;
		case 4:
			SS.insert();  //if verified, all inputs will be inserted into customer database
			cout << "\n\t\t\t\t\t\t\t\tSuccessfully registered." << endl; _getch();
			return;
			break;
		case 5:
			return;
			break;
		default: break;
		}
	}
}

void slogin()  //existing customer log in
{
	S_Menu menu;
	menu.header = "       Login       ";
	menu.addOption("        Email       ");
	menu.addOption("       Password     ");
	menu.addOption("        Login       ");
	menu.addOption("         Back       ");

	S_Staff SS;
	int option = 0;

	while (1)
	{
		option = menu.prompt1(option);
		switch (option)
		{
		case -1:
			return;
			break;
		case 0:
			cout << "\n\t\t\t\t\t\t\t\tEmail " << char(175) << " ";
			cin >> SS.S_Email;
			menu.setValue(0, SS.S_Email);
			break;
		case 1:
			cout << "\n\t\t\t\t\t\t\t\tPassword " << char(175) << " ";
			cin >> SS.S_Password;
			menu.setValue(1, hidepwd(SS.S_Password));
			break;
		case 2:
			if (SS.login())  //if user's inputs match with any data in database, it will return true and proceed
			{
				shome(SS);
			}
			else
			{
				cout << "\t\tInvalid Email or Password"; _getch();
			}
			break;
		case 3:
			return;
			break;
		default: break;
		}
	}
}

void shome(S_Staff SS)  //page when when staff successfully logged in
{
	S_Menu menu;
	menu.addOption("     New Package    ");
	menu.addOption("Package Sales Report");
	menu.addOption("      Logout        ");

	int option = 0;

	while (1)
	{
		menu.header = "        Home       ";
		option = menu.prompt2(option);

		switch (option)
		{
		case -1:
			return;
			break;
		case 0:
			newpackage(SS);
			break;
		case 1:
			viewsummary();
			break;
		case 2:
			return;
			break;
		default: break;
		}
	}
}

void newpackage(S_Staff SS)  //add new package
{
	S_Menu menu;
	menu.header = "    New Package    ";
	menu.addOption("        Name*       ");
	menu.addOption("        Price*      ");
	menu.addOption("       Detail*      ");
	menu.addOption("        Hour*       ");
	menu.addOption("         Add        ");
	menu.addOption("         Back       ");
	menu.footer = "* - mandatory";

	S_Package SP;
	SP.StaffID = SS.StaffID;
	int option = 0;
	string tmp;

	while (1)
	{
		option = menu.prompt1(option);
		switch (option)
		{
		case -1:
			return;
			break;
		case 0:
			cout << "\n\t\t\t\t\t\t\t\tName " << char(175) << " ";
			getline(cin >> ws, SP.P_Name);
			menu.setValue(0, SP.P_Name);  //to display user's input
			break;
		case 1:
			cout << "\n\t\t\t\t\t\t\t\tPrice RM " << char(175) << " ";
			cin >> SP.P_Price;
			menu.setValue(1, to_string(SP.P_Price));
			break;
		case 2:
			cout << "\n\t\t\t\t\t\t\t\tDetail " << char(175) << " ";
			getline(cin >> ws, SP.P_Detail);
			menu.setValue(2, SP.P_Detail);
			break;
		case 3:
			cout << "\n\t\t\t\t\t\t\t\tHour " << char(175) << " ";
			cin >> SP.P_Hour;
			menu.setValue(3, to_string(SP.P_Hour));
			break;
		case 4:
			SP.insert();
			cout << "\n\t\t\t\t\t\t\t\tSuccessfully Added." << endl; _getch();
			return;
			break;
		case 5:
			return;
			break;
		default: break;
		}
	}
}

void viewsummary()
{
	vector <S_Report> report;
	vector <S_Review> review;
	S_Menu menu;
	menu.header = "      Summary      ";
	menu.addOption("    Sales Report    ");
	menu.addOption("    View Reviews    ");
	menu.addOption("        Back        ");

	while (1)
	{
		switch (menu.prompt2())
		{
		case -1:
			return;
			break;
		case 0:
			cout << "\n\t\t\t\t\t\t\t\tMonth " << char(175) << " ";
			cin >> month;
			cout << "\n\t\t\t\t\t\t\t\tYear " << char(175) << " ";
			cin >> year;

			report = S_Report::summary(month, year);
			cout << "\n\t\t\t\t\t\t* Packages Sales and Review Report for month " + to_string(month) + " of " + to_string(year) + " * \n";

			cout << "\n\t\t\t\t" << "*" << setw(11) << "Package ID" << setw(2) << "*"
				<< setw(13) << "By (StaffID)" << setw(2) << "*"
				<< setw(18) << "No of Reservation" << setw(2) << "*"
				<< setw(21) << "Reservation Reviewed" << setw(2) << "*"
				<< setw(13) << "Average Rate" << setw(2) << "*";
			cout << "\n\t\t\t\t***************************************************************************************";

			for (int i = 0; i < report.size(); i++)
			{
				cout << "\n\t\t\t\t" << "*" << setw(11) << report[i].PackageID << setw(2) << "*"
					<< setw(13) << report[i].StaffID << setw(2) << "*"
					<< setw(18) << report[i].Reserved << setw(2) << "*"
					<< setw(21) << report[i].ReservationReviewed << setw(2) << "*"
					<< setw(13) << fixed << setprecision(2) << report[i].AverageRate << setw(2) << "*";
			} 
			cout << "\n\n\t\t\t\tNote : Average rate is calculated only from reviews that are entered by customers."; _getch();

			break;
		case 1:
			cout << "\n\t\t\t\t\t\t\t\tPackage ID " << char(175) << " ";
			cin >> id;

			review = S_Review::findReview(id);  //using the id to find matching PackageID in review database
			cout << "\n\t\t\t\t\t\t\t\t* Reviews for Package " + to_string(id) + " * \n";

			for (int i = 0; i < review.size(); i++)
			{
				cout << "\n\t\t\t\t\t\t\t\tFrom " << review[i].C_FirstName;
				cout << "\n\t\t\t\t\t\t\t\tRate >> " << review[i].R_Rate << " / 5";
				cout << "\n\t\t\t\t\t\t\t\tComment >> " << review[i].R_Comment << endl;
			}
			_getch();

			break;
		case 2:
			return;
			break;
		default: break;
		}
	}
}

void cregistration()  //registering new customer
{
	S_Menu menu;
	menu.header = "    Registration   ";
	menu.addOption("     First Name*    ");
	menu.addOption("      Last Name*    ");
	menu.addOption("       Address*     ");
	menu.addOption("      Post Code*    ");
	menu.addOption("        City*       ");
	menu.addOption("        State*      ");
	menu.addOption("       Contact*     ");
	menu.addOption("        Email*      ");
	menu.addOption("       Password*    ");
	menu.addOption("       Register     ");
	menu.addOption("         Back       ");
	menu.footer = "* - mandatory";

	S_Account SA;
	int option = 0;
	string tmp;

	while (1)
	{
		option = menu.prompt1(option);
		switch (option)
		{
		case -1:
			return;
			break;
		case 0:
			cout << "\n\t\t\t\t\t\t\t\tFirst Name " << char(175) << " ";
			cin >> SA.C_FirstName;
			menu.setValue(0, SA.C_FirstName);  //to display user's input
			break;
		case 1:
			cout << "\n\t\t\t\t\t\t\t\tLast Name " << char(175) << " ";
			cin >> SA.C_LastName;
			menu.setValue(1, SA.C_LastName);
			break;
		case 2:
			cout << "\n\t\t\t\t\t\t\t\tAddress " << char(175) << " ";
			getline(cin >> ws, SA.C_Address);  //combine string with space
			menu.setValue(2, SA.C_Address);
			break;
		case 3:
			cout << "\n\t\t\t\t\t\t\t\tPost Code " << char(175) << " ";
			cin >> SA.C_PostCode;
			menu.setValue(3, to_string(SA.C_PostCode));
			break;
		case 4:
			cout << "\n\t\t\t\t\t\t\t\tCity " << char(175) << " ";
			getline(cin >> ws, SA.C_City);
			menu.setValue(4, SA.C_City);
			break;
		case 5:
			cout << "\n\t\t\t\t\t\t\t\tState " << char(175) << " ";
			getline(cin >> ws, SA.C_State);
			menu.setValue(5, SA.C_State);
			break;
		case 6:
			cout << "\n\t\t\t\t\t\t\t\tContact " << char(175) << " ";
			cin >> SA.C_Contact;
			menu.setValue(6, SA.C_Contact);
			break;
		case 7:
			cout << "\n\t\t\t\t\t\t\t\tEmail " << char(175) << " ";
			cin >> SA.C_Email;
			menu.setValue(7, SA.C_Email);
			break;
		case 8:  //to do: make sure that password is cencored
			do
			{
				cout << "\n\t\t\t\t\t\t\t\tPassword " << char(175) << " ";
				cin >> tmp;

				if (tmp.length() > 5 && tmp.length() < 13)  //make sure that password length is more than 5 digits and lest than 13 digits
				{
					SA.C_Password = tmp;
					menu.setValue(8, SA.C_Password);
				}
				else
					cout << "\n\t\t!!Password must be 6 to 12 character!!" << endl;

			} while (tmp.length() <= 5 || tmp.length() >= 13);
			break;
		case 9:
			SA.insert();  //if verified, all inputs will be inserted into customer database
			cout << "\n\t\t\t\t\t\t\t\tSuccessfully registered." << endl; _getch();
			return;
			break;
		case 10:
			return;
			break;
		default: break;
		}
	}
}

void clogin()  //existing customer log in
{
	S_Menu menu;
	menu.header = "       Login       ";
	menu.addOption("        Email       ");
	menu.addOption("       Password     ");
	menu.addOption("        Login       ");
	menu.addOption("         Back       ");

	S_Account SA;
	int option = 0;

	while (1)
	{
		option = menu.prompt1(option);
		switch (option)
		{
		case -1:
			return;
			break;
		case 0:
			cout << "\n\t\t\t\t\t\t\t\tEmail " << char(175) << " ";
			cin >> SA.C_Email;
			menu.setValue(0, SA.C_Email);
			break;
		case 1:
			cout << "\n\t\t\t\t\t\t\t\tPassword " << char(175) << " ";
			cin >> SA.C_Password;
			menu.setValue(1, hidepwd(SA.C_Password));
			break;
		case 2:
			if (SA.login())  //if user's inputs match with any data in database, it will return true and proceed
			{
				chome(SA);
			}
			else
			{
				cout << "\t\tInvalid Email or Password"; _getch();
			}
			break;
		case 3:
			return;
			break;
		default: break;
		}
	}
}

void chome(S_Account SA)  //page when when customer successfully logged in
{
	S_Menu menu;
	menu.addOption("    Edit Account    ");
	menu.addOption("    Reservation     ");
	menu.addOption("      Feedback      ");
	menu.addOption("      Logout        ");

	int option = 0;

	while (1)
	{
		menu.header = "        Home       ";
		option = menu.prompt2(option);

		switch (option)
		{
		    case -1:
				return;
				break;
			case 0:
				SA = cedit(SA);
				break;
		    case 1:
				RAction(SA);
				break;
			case 2:
				feedback(SA);
				break;
			default:
				return;
				break;
		}
	}
}

S_Account cedit(S_Account SA) // edit customer's account
{
	S_Menu menu;
	menu.header = " Edit Your Profile ";
	menu.addOption("     First Name     ");
	menu.addOption("      Last Name     ");
	menu.addOption("       Address      ");
	menu.addOption("      Post Code     ");
	menu.addOption("        City        ");
	menu.addOption("        State       ");
	menu.addOption("       Contact      ");
	menu.addOption("       Password     ");
	menu.addOption("        Edit        ");
	menu.addOption("       Delete       ");
	menu.addOption("        Back        ");
	menu.footer = "Your email cannot be changed.";

	S_Account temp = SA;
	string tmp;

	while (1)
	{
		menu.setValue(0, temp.C_FirstName);
		menu.setValue(1, temp.C_LastName);
		menu.setValue(2, temp.C_Address);
		menu.setValue(3, to_string(temp.C_PostCode));
		menu.setValue(4, temp.C_City);
		menu.setValue(5, temp.C_State);
		menu.setValue(6, temp.C_Contact);
		menu.setValue(7, temp.C_Password);

		switch (menu.prompt1())
		{
		case -1:
			return SA;
			break;
		case 0:
			cout << "\n\t\t\t\t\t\t\t\tFirst Name " << char(175) << " ";
			cin >> temp.C_FirstName;
			break;
		case 1:
			cout << "\n\t\t\t\t\t\t\t\tLast Name " << char(175) << " ";
			cin >> temp.C_LastName;
			break;
		case 2:
			cout << "\n\t\t\t\t\t\t\t\tAddress " << char(175) << " ";
			getline(cin >> ws, temp.C_Address);  //combine string with space
			break;
		case 3:
			cout << "\n\t\t\t\t\t\t\t\tPost Code " << char(175) << " ";
			cin >> temp.C_PostCode;
			break;
		case 4:
			cout << "\n\t\t\t\t\t\t\t\tCity " << char(175) << " ";
			getline(cin >> ws, temp.C_City);
			break;
		case 5:
			cout << "\n\t\t\t\t\t\t\t\tState " << char(175) << " ";
			getline(cin >> ws, temp.C_State);
			break;
		case 6:
			cout << "\n\t\t\t\t\t\t\t\tContact " << char(175) << " ";
			cin >> temp.C_Contact;
			break;
		case 7:  //to do: make sure that password is cencored
			do
			{
				cout << "\n\t\t\t\t\t\t\t\tPassword " << char(175) << " ";
				cin >> tmp;

				if (tmp.length() > 5 && tmp.length() < 13)  //make sure that password length is more than 5 digits and lest than 13 digits
				{
					temp.C_Password = tmp;
				}
				else
					cout << "\n\t\t!!Password must be 6 to 12 character!!" << endl;

			} while (tmp.length() <= 5 || tmp.length() >= 13);
			break;
		case 8:
			SA = temp;
			SA.update();
			cout << "\n\t\t\t\t\t\t\t\tSuccessfully updated." << endl; _getch();
			break;
		case 9:
			cout << "\n\t\t\t\t\t\t\t\tAre you sure you want to delete the account ? [Y - yes] " << char(175) << " ";
			char cdelete;
			cin >> cdelete;
			if (cdelete == 'Y' || cdelete == 'y')
			{
				SA = temp;
				SA.remove();
				cout << "\n\t\t\t\t\t\t\t\tAccount deleted." << endl; _getch();
				main();
			}
			break;
		case 10:
			return SA;
			break;
		default: break;
		}
	}
}

void feedback(S_Account SA)
{
	S_Reservation SR;
	vector <S_Review> review;
	SR.CustomerID = SA.CustomerID;  //setting CustomerID in reservation database to be the same as logged-in customer's CustomerID

	S_Menu menu;
	menu.header = "       Review      ";
	menu.addOption("    Leave Review    ");
	menu.addOption("        Back        ");

	S_Menu menu2;
	menu2.header = " Leave Your Review ";
	menu2.addOption("        Rate*       ");
	menu2.addOption("       Comment      ");
	menu2.addOption("        Enter       ");
	menu2.footer = "* - mandatory";
	string displayString = "";

	while (1)
	{
		if (displayString == "")
		{
			stringstream tmpString; 
			review = S_Review::viewreview();  //using the id to find matching PackageID in package database
			displayString = "\n\t\t\t\t\t\t\t\t  * Review for Packages * \n";

			for (int i = 0; i < review.size(); i++)
			{
				tmpString << "\n\t\t\t\t\t\t\t\tFrom " << review[i].C_FirstName;
				tmpString << "\t\tPackage >> " << review[i].PackageID;
				tmpString << "\n\t\t\t\t\t\t\t\tRate >> " << review[i].R_Rate << " / 5";
				tmpString << "\n\t\t\t\t\t\t\t\tComment >> " << review[i].R_Comment << endl;
			}

			displayString += tmpString.str();
		}
		menu.footer = displayString;

		switch (menu.prompt2())
		{
		case -1:
		    return;
			break;
		case 0:
			cout << "\n\t\t\t\t\t\t\t\tEnter Reservation ID to review [0 - back] " << char(175) << " ";
			int RID;
			cin >> RID;

			SR = S_Reservation::findReservation(SR.CustomerID, RID);  //find if inserted ReservationID match with customer's reservation database
			if (SR.ReservationID == 0 && !checkdate(SR.R_Date))  //check if id exist and reservation date is in the past
			{
				cout << "\n\t\t\tReservation not found";
				_getch();
			}
			else
			{
				S_Review SS; SS.ReservationID = RID;
				bool loop = true;
				while (loop)
				{
					switch (menu2.prompt1())
					{
					case -1:
						return;
						break;
					case 0:
						cout << "\n\t\t\t\t\t\t\t\tRate [?/5] " << char(175) << " ";
						cin >> SS.R_Rate;
						menu2.setValue(0, to_string(SS.R_Rate));
						continue;
					case 1:
						cout << "\n\t\t\t\t\t\t\t\tComment " << char(175) << " ";
						getline(cin >> ws, SS.R_Comment);
						menu2.setValue(1, SS.R_Comment);
						continue;
					default:
						cout << "\n\t\t\t\t\t\t\t\tAre you sure to enter this review ? [Y - yes | X - no/back] " << char(175) << " ";
						char leavereview;
						cin >> leavereview;
						if (leavereview == 'Y' || leavereview == 'y')
						{
							if (SS.R_Rate >= 0 && SS.R_Rate <= 5)
							{
								SS.addreview();
								cout << "\n\t\t\t\t\t\t\t\tDone"; _getch();
								loop = false;
							}
							else
							{
								cout << "\n\t\t\t\t\t\t\t\tPlease enter the rate"; _getch();
							}
						}
						else
							loop = false;
						continue;
					}
				}
				break;
			}
			break;
		default:
			return;
			break;
		}
	}
}

void RAction(S_Account SA)  //page for customer that want to act regarding reservation request
{
	S_Reservation SR;
	SR.CustomerID = SA.CustomerID;  //setting CustomerID in reservation database to be the same as logged-in customer's CustomerID

	S_Menu menu;
	menu.addOption("      Request       ");
	menu.addOption("    View Request    ");
	menu.addOption("        Back        ");

	int option = 0;

	while (1)
	{
		menu.header = "    Reservation    ";
		option = menu.prompt2(option);

		switch (option)
		{
		case -1:
			return;
			break;
		case 0:
			reservation(SA);
			break;
		case 1:
			view(SA);
			break;
		default:
			return;
			break;
		}
	}
}

void view(S_Account SA)  //displaying all reservations made by the logged-in customer
{
	vector<S_Reservation> reservation;
	string displayString;

	S_Menu menu;
	menu.header = " Your Reservations ";
	menu.addOption("        Back        ");

	int option = 0;

	while (1)
	{
		reservation = S_Reservation::viewreservations(SA.CustomerID);
		displayString = "";
		if (displayString == "")
		{
			displayString = "\n\t\t\t\t\t\t\t\t   *Your Reservations*\n\n";
			stringstream tmpString;

			tmpString << "\n\t\t\t\t" << "*" << setw(15) << "Reservation ID" << setw(2) << "*"
				<< setw(11) << "Package ID" << setw(2) << "*"
				<< setw(14) << "Extra Cleaner" << setw(2) << "*"
				<< setw(5) << "Tool" << setw(2) << "*"
				<< setw(11) << "Date" << setw(2) << "*"
				<< setw(9) << "Time" << setw(2) << "*"
				<< setw(11) << "Total (RM)" << setw(2) << "*";
				                                //<< setw(15) << "Description" << setw(2) << char(42);
			tmpString << "\n\t\t\t\t*******************************************************************************************";
			for (int i = 0; i < reservation.size(); i++)
			{
				tmpString << "\n\t\t\t\t" << "*" << setw(15) << reservation[i].ReservationID << setw(2) << "*"
					<< setw(11) << reservation[i].PackageID << setw(2) << "*"
					<< setw(14) << reservation[i].R_Extra << setw(2) << "*"
					<< setw(5) << reservation[i].R_Tool << setw(2) << "*"
					<< setw(11) << reservation[i].R_Date << setw(2) << "*"
					<< setw(9) << reservation[i].R_Time << setw(2) << "*"
					<< fixed << setprecision(2) << setw(11) << reservation[i].R_Total << setw(2) << "*";
					//<< setw(20) << reservation[i].R_Description << setw(2) << char(42);
			}

			displayString += tmpString.str();
		}
		menu.footer = displayString;

		option = menu.prompt2(option);

		switch (option)
		{
		case -1:
			return;
			break;
		default:
			return;
			break;
		}
	}
}

void reservation(S_Account SA)  //page for customer to make reservation request
{
	S_Reservation SR;
	SR.CustomerID = SA.CustomerID;

	S_Menu menu;
	menu.addOption("       Package*     ");
	menu.addOption("    Extra Cleaner   ");
	menu.addOption("        Tools*      ");
	menu.addOption("         Date*      ");
	menu.addOption("         Time*      ");
	menu.addOption("     Description    ");
	menu.addOption("       Reserve      ");
	menu.addOption("         Back       ");
	menu.footer = "* - mandatory";

	int option = 0;
	string tempdate;

	while (1)
	{
		menu.header = "    Reservation    ";

		option = menu.prompt1(option); 

		switch (option)
		{
		    case -1:
				return;
				break;
			case 0:
				SR = package(SA, SR);
				menu.setValue(0, to_string(SR.items1.PackageID));
				break;
			case 1:
				cout << "\n\t\t\t\t\t\t\tEach extra cleaner will add RM 25.00/hour to the cost" << endl; SR.R_Extra = 0;
				cout << "\n\t\t\t\t\t\t\t\tExtra Cleaner [0 - None] " << char(175) << " ";
				int extra;
				cin >> extra;

				if (extra > 0)
				{
					SR.R_Extra = extra;
				}

				menu.setValue(1, to_string(SR.R_Extra));
				break;
			case 2:
				cout << "\n\t\t\t\t\t\t\t\tCleaning Tools - RM 55" << endl;
				cout << "\n\t\t\t\t\t\t\t\tTools [Y/y - yes] " << char(175) << " ";
				char tools;
				cin >> tools;

				if (tools == 'y' || tools == 'Y')
				{
					SR.R_Tool = "Yes"; SR.tool = true;  //true, false is for total calculation purpose
				}
				else
					SR.tool = false;

				menu.setValue(2, SR.R_Tool);
				break;
			case 3:
			    cout << "\n\t\t\t\t\t\t\t\tDay " << char(175) << " ";
				cin >> day;
						
			    cout << "\n\t\t\t\t\t\t\t\tMonth " << char(175) << " ";
				cin >> month;
						
				cout << "\n\t\t\t\t\t\t\t\tYear " << char(175) << " ";
				cin >> year;

			    tempdate = to_string(day) + "-" + to_string(month) + "-" + to_string(year);

				if (checkdate(tempdate))  // to see if date entered surpass current date and exist
				{
					SR.R_Date = tempdate;  //rearrange the date inputs
				}
				else
					cout << "\n\t\t\t\t\t\t\t\tDate entered is invalid."; _getch();
				
				menu.setValue(3, SR.R_Date);
				break;
			case 4:
				cout << "\n\t\t\t\t\t\t\t\tTime HH:MM " << char(175) << " ";
				cin >> SR.R_Time;
				menu.setValue(4, SR.R_Time);
				break;
			case 5:
				cout << "\n\t\t\t\t\t\t\t\tDescription " << char(175) << " ";
				getline(cin >> ws, SR.R_Description);
				menu.setValue(5, SR.R_Description);
				break;
			case 6:  //to do:what happen if customer dont complete the request but proceed to reserve?
				if (SR.items1.PackageID != 0 && SR.R_Date != "" && SR.R_Time != "") {
					SR.R_Total = SR.totalreservation();  //calculate the total based on the customer's input
					cout << "\n\t\t\t\t\t\t\tTotal : RM " << fixed << setprecision(2) << to_string(SR.R_Total) << endl;

					cout << "\n\t\t\t\t\t\t\t\tReserve ? [y - Yes] " << char(175) << " ";
					char confirm;
					cin >> confirm;
					if (confirm == 'y' || confirm == 'Y')
					{
						SR.addreservation();  //if customer is sure about their reservation request, the proceed to insert data into database
						cout << "\n\t\t\t\t\t\t\t\tReservation successful."; _getch();
					}
				}
				else
					cout << "\n\t\t\t\t\t\t\t\tIncomplete information for reservation. Please provide all necessary details."; _getch();
				break;
			default:
				return;
				break;
		}
	}
}

S_Reservation package(S_Account SA, S_Reservation SR)  //page for package selection
{
	vector<S_Package> package;
	string displayString;

	S_Menu menu;
	menu.header = "      Package      ";
	menu.addOption("   Choose Package   ");
	menu.addOption("        Back        ");

	int option = 0;

	while (1)
	{
		package = S_Package::findPackage();  //find all available packages to display
		displayString = "";
		if (displayString == "")
		{
			displayString = "\n\t\t\t\t\t\t\t\t  *Packages Available*\n\n";
			stringstream tmpString;

			tmpString << "\t\t*" << setw(3) << "ID" << setw(2) << "*" << setw(15) << "Name" << setw(4) << "*" << setw(11) << "Price (RM)" << setw(2) << "*" << setw(75) << "Detail" << setw(2) << "*" << setw(9) << "Duration" << setw(2) << "*" << setw(15) << "Cleaner Amount" << setw(2) << "*";
			tmpString << "\n\t\t***********************************************************************************************************************************************";
			for (int i = 0; i < package.size(); i++)
			{
				tmpString << "\n\t\t*" << setw(3) << package[i].PackageID << setw(2) << "*" << setw(15) << package[i].P_Name << setw(4) << "*" << setw(11) << fixed << setprecision(2) << package[i].P_Price << setw(2) << "*" << setw(75) << package[i].P_Detail << setw(2) << "*" << setw(9) << package[i].P_Hour << setw(2) << "*" << setw(15) << package[i].P_CleanerAmount << setw(2) << "*";
			}

			displayString += tmpString.str();
		}
		menu.footer = displayString;

		option = menu.prompt2(option);

		switch (option)
		{
		    case -1:
				return SR;
				break;
			case 0:
				cout << "\n\n\t\t\t\t\t\t\t\t Choose Package ID " << char(175) << " ";
				cin >> id;
				SR = findpackage(SA, id, SR);  //to find if PackageID requested by customer exist
				break;
			default:
				return SR;
				break;
		}
	}
}

S_Reservation findpackage(S_Account SA, int id, S_Reservation SR)  //to find if PackageID requested exist
{	
	S_Package package = S_Package::findPackage(id);  //using the id to find matching PackageID in package database

	if (package.PackageID == 0)
	{
		cout << "\n\t\t\tPackage not found";
		_getch();
		return SR;
	}

	SR.addpackage(package);  //if found, add the details about the PackageID into reservation database
	cout << "\n\n\t\t\t\t\t\t\t\tPackage added."; _getch();
	return SR;
}

string hidepwd(string pwd) 
{
	string hidden = "";
	for (int i = 0; i < pwd.size(); i++) 
	{
		hidden += '*';
	}
	return hidden;
}

bool checkdate(const string& dateinput)
{
	std::tm inputdate = {};
	std::istringstream ss(dateinput);
	char dash;  // to store the dash between day, month, and year
	ss >> inputdate.tm_mday >> dash >> inputdate.tm_mon >> dash >> inputdate.tm_year;

	// Adjust the year and month to match the structure representation
	inputdate.tm_year -= 1900;
	inputdate.tm_mon -= 1;

	// Get the current date
	std::tm currentDate;
	auto currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	localtime_s(&currentDate, &currentTime);

	// Convert both dates to time points for easy comparison
	auto currentTimePoint = std::chrono::system_clock::from_time_t(currentTime);
	auto userInputTimePoint = std::chrono::system_clock::from_time_t(std::mktime(&inputdate));

	return (userInputTimePoint > currentTimePoint) && (inputdate.tm_year == year - 1900) && (inputdate.tm_mon == month - 1) && (inputdate.tm_mday == day);
}