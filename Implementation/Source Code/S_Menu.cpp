#include "S_Menu.h"
#include <iostream>
#include <conio.h>
using namespace std;

S_Menu::S_Menu() {
	bullet = char(175);
	limit = 10;
}

int S_Menu::prompt1(int selected) 
{
	// selected is the optional paramter, by default if no value is passed we assume the initial selection is at index 0, the first item
	int before = limit / 2;
	int after = limit - before;
	char option = '\0';
	while (1) {

		system("cls");
		cout << "\n\t\t\t\t\t\t\t\t " << char(201);      for (int i = 0; i < 19; i++) { cout << char(205); }      cout << char(187) << endl;
		cout << "\t\t\t\t\t\t\t\t " << char(42) << header << char(42) << endl;
		cout << "\t\t\t\t\t\t\t\t " << char(200);      for (int i = 0; i < 19; i++) { cout << char(205); }      cout << char(188) << endl << endl;

		for (int i = 0; i < items.size(); i++)
		{

			if (selected < before) {
				if (i >= limit) {
					continue;
				}
			}
			else if (selected >= items.size() - limit) {
				if (i < (items.size() - limit)) {
					continue;
				}
			}
			else if (((items.size() - 1 - selected) >= limit)) {
				if (i > selected + after || i <= selected - before) {

					continue;
				}

			}
			if (selected == i) {
				cout << "\u001b[33m"; //if it is selected option we set the console text color to yellow/gold
			}
			cout << "\t\t\t\t\t\t\t\t" << char(42) << " " << items[i].first << char(42) << endl;
			if (items[i].second.length() > 0) {
				cout << "\t\t\t\t\t\t\t\t" << bullet << " " << items[i].second << endl;
			}
			cout << endl;
			if (selected == i) {
				cout << "\u001b[0m"; // this code reset backs the color to default colouring
			}
		}

		cout << endl << "\t\t\t\t\t\t\t\t " << footer << endl;
		option = _getch();

		//cast the character returned by getch to int which will be its ASCII code
		if (int(option) == -32) {
			//-32 is the first ASCII code sent to buffer to indicate escape character for special character. 
			// this is necessary since without the escape character some special character such as arrow keys overlaps with normal character ASCII
			// -32 is sent first to input bufer, which mean for special character there are actually character sent to buffer
			// so we need to getch one more time to capture the actual character for the key being pressed
			option = _getch();
			switch (option)
			{
			case 72: // 72 is the ASCII code for up arrow
				if (selected > 0) {
					// iff selected is greater than 0 and up arrow is pressed we decrease the selected index
					selected--;
				}
				else {
					selected = items.size() - 1; //if we can't decreament when user already at first item we move selection to last instead
				}
				break;
			case 80: // 80 is the ASCII code for down arrow
				if (selected < items.size() - 1) {
					// if selected is less than lass index we increment
					selected++;
				}
				else {
					selected = 0; // if we can't increment means that it is last item, we move selected back to the top
				}
				break;
			}
		}
		else {
			// if the frst character sent to buffer after getch is not -32 means that it is normal character so we can process accordingly
			if (option == 27) {
				// 27 is the ASCII code for "ESCAPE"
				// when user press escape we exit from the loop and just return -1 to indicate user cancel selection
				return -1;

			}
			else if (option == '\r') {
				// we can also compare the integer with character like this, \r is carriage return aka enter
				// when enter is pressed we assume user want to proceed, so we return the selected
				return selected;

			}
		}
	}

}

int S_Menu::prompt2(int selected)
{
	// selected is the optional paramter, by default if no value is passed we assume the initial selection is at index 0, the first item
	int before = limit / 2;
	int after = limit - before;
	char option = '\0';
	while (1) {

		system("cls");
		cout << "\n\t\t\t\t\t\t\t\t " << char(201);      for (int i = 0; i < 19; i++) { cout << char(205); }      cout << char(187) << endl;
		cout << "\t\t\t\t\t\t\t\t " << char(42) << header << char(42) << endl;
		cout << "\t\t\t\t\t\t\t\t " << char(200);      for (int i = 0; i < 19; i++) { cout << char(205); }      cout << char(188) << endl << endl;

		cout << "\t\t\t\t\t\t\t\t" << char(218);  for (int i = 0; i < 23; i++) { cout << char(196); } cout << char(191) << endl;
		for (int i = 0; i < items.size(); i++)
		{

			if (selected < before) {
				if (i >= limit) {
					continue;
				}
			}
			else if (selected >= items.size() - limit) {
				if (i < (items.size() - limit)) {
					continue;
				}
			}
			else if (((items.size() - 1 - selected) >= limit)) {
				if (i > selected + after || i <= selected - before) {

					continue;
				}

			}
			if (selected == i) {
				cout << "\u001b[33m"; //if it is selected option we set the console text color to yellow/gold
			}
			cout << "\t\t\t\t\t\t\t\t" << char(42) << " " << bullet << items[i].first << char(42) << endl;
			if (items[i].second.length() > 0) {
				cout << " : " << items[i].second;
			}
			cout << endl;
			if (selected == i) {
				cout << "\u001b[0m"; // this code reset backs the color to default colouring
			}
		}
		cout << "\t\t\t\t\t\t\t\t" << char(192);  for (int i = 0; i < 23; i++) { cout << char(196); } cout << char(217) << endl;

		cout << endl << "\t\t\t\t\t\t\t\t " << footer << endl;
		option = _getch();

		//cast the character returned by getch to int which will be its ASCII code
		if (int(option) == -32) {
			//-32 is the first ASCII code sent to buffer to indicate escape character for special character. 
			// this is necessary since without the escape character some special character such as arrow keys overlaps with normal character ASCII
			// -32 is sent first to input bufer, which mean for special character there are actually character sent to buffer
			// so we need to getch one more time to capture the actual character for the key being pressed
			option = _getch();
			switch (option)
			{
			case 72: // 72 is the ASCII code for up arrow
				if (selected > 0) {
					// iff selected is greater than 0 and up arrow is pressed we decrease the selected index
					selected--;
				}
				else {
					selected = items.size() - 1; //if we can't decreament when user already at first item we move selection to last instead
				}
				break;
			case 80: // 80 is the ASCII code for down arrow
				if (selected < items.size() - 1) {
					// if selected is less than lass index we increment
					selected++;
				}
				else {
					selected = 0; // if we can't increment means that it is last item, we move selected back to the top
				}
				break;
			}
		}
		else {
			// if the frst character sent to buffer after getch is not -32 means that it is normal character so we can process accordingly
			if (option == 27) {
				// 27 is the ASCII code for "ESCAPE"
				// when user press escape we exit from the loop and just return -1 to indicate user cancel selection
				return -1;

			}
			else if (option == '\r') {
				// we can also compare the integer with character like this, \r is carriage return aka enter
				// when enter is pressed we assume user want to proceed, so we return the selected
				return selected;

			}
		}
	}

}

void S_Menu::addOption(string text, string value) 
{
	items.push_back({ text,value });
}

void S_Menu::clearOption() 
{
	items.clear();
}

void S_Menu::setValue(int index, string value) 
{
	if (index >= 0 && index < items.size()) {
		items[index].second = value;
	}
}