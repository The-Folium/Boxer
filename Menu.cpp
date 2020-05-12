#include "Menu.h"


extern Logger Log;

Menu::Menu(std::string name) :menuName{ name }
{
}

void Menu::addOption(std::string option_caption)
{
	options.push_back(option_caption);
}

int Menu::askOption()
{
	auto longestOptionIter{ std::max_element(options.begin(), options.end(), comparator) };
	size_t menuWidth{ std::max(longestOptionIter->length() + 2, menuName.length() + 2)};
	if (menuWidth % 2) {++menuWidth;}

	Log.nextLineToConsole();	
	std::string spaces((menuWidth - menuName.length()) / 2, ' ');
	Log.toConsole(spaces + menuName +spaces +'\n' + std::string(menuWidth, '-') + '\n');
	Log.nextLineToConsole();

	for (unsigned int i{ 0 }; i < options.size(); ++i)
	{
		Log.toConsole(std::to_string(i+1) + ". " + options[i] + "\n");
	}

	Log.nextLineToConsole();

	return Log.inputInt("Enter [1.." + std::to_string(options.size()) + "]: ",std::make_pair(1, options.size()));
		
	
}


