#include "Menu.h"
extern Logger Log;

Menu::Menu(const std::string& name) :menuName{ name }
{
}

void Menu::addOption(const std::string& option_caption)
{
	options.push_back(option_caption);
}

int Menu::askOption()
{
	size_t menuWidth{ getMenuWidth() };

	if (menuWidth % 2) {++menuWidth;}

	Log.nextLine(Logger::CONSOLE);	
	std::string spaces((menuWidth - menuName.length()) / 2, ' ');
	Log.print(Logger::CONSOLE, spaces + menuName +spaces +'\n' + std::string(menuWidth, '-') + '\n');
	Log.nextLine(Logger::CONSOLE);

	for (unsigned int i{ 0 }; i < options.size(); ++i)
	{
		Log.print(Logger::CONSOLE, std::to_string(i+1) + ". " + options[i] + "\n");
	}

	Log.nextLine(Logger::CONSOLE);

	return Log.inputInt("Enter [1.." + std::to_string(options.size()) + "]: ",std::make_pair(1, options.size()));			
}

size_t Menu::getMenuWidth()
{
	auto longestOptionIter{ std::max_element(options.begin(), options.end(), comparator) };
	size_t menuWidth{ std::max(longestOptionIter->length() + 2, menuName.length() + 2) };
	if (menuWidth % 2) { ++menuWidth; }
	return menuWidth;
}
