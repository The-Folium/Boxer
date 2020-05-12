#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "Log.h"

class Menu
{
	std::string menuName;
	std::vector<std::string> options;

public:
	Menu(const std::string& name);
	void addOption(const std::string& option_caption);
	int askOption();

private:
	static bool comparator(const std::string& option1, const std::string& option2)
	{
		return option1.length() < option2.length();
	}

	size_t getMenuWidth();
};