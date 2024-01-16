#pragma once
#ifndef S_MENU_H
#define S_MENU_H

#include <string>
#include <vector>
#include <utility>

class S_Menu
{
public:
	std::string header, footer, bullet, separator;
	// separator will be used to divide headder footer and the options. since it is attribute it can be modified --- is only the default value

	std::vector<std::pair<std::string, std::string>> items;
	// first part of the pair will be the text, second part is value if any
	int limit;

	void addOption(std::string option, std::string value = "");
	void setValue(int index, std::string text);
	void clearOption();


	S_Menu();
	int prompt1(int = 0);
	int prompt2(int = 0);
};

#endif