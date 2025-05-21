#pragma once 
#ifndef S_ARMENU
#define S_ARMENU

#include <string>
#include <vector>
#include <utility>

class S_ARMenu
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


	S_ARMenu();
	int prompt(int = 0);
};

#endif