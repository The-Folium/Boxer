#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <utility>


class Logger
{
	std::string logPath;
	std::ofstream logFile;

public:
	Logger(std::string path) : logPath{ path }
	{
		logFile.open(path);
	}

	~Logger()
	{
		logFile.close();
	}

	void newLogFile(std::string path)
	{
		logFile.close();
		logFile.open(path);
	}

	void toConsole(std::string text)
	{
		std::cout << text;
	}

	void nextLineToConsole(int count = 1)
	{
		for (int i{ 0 }; i < count; ++i)
		{
			std::cout << std::endl;
		}
	}

	void nextLineToFile()
	{
		logFile << '\n';
	}

	void toFile(std::string text)
	{
		logFile << text;
	}
		
	int inputInt(std::string text, std::pair<int, int> limits)
	{
		int input{1};		
		std::cin.clear();
		bool failFlag{ false };
		do
		{			
			if (failFlag)
			{
				toConsole("Incorrect input. Try again.\n");
			}
			toConsole(text);
			std::cin.clear();
			std::string str_input{};
			std::cin >> str_input;
			failFlag = false;
			try
			{
				input =  std::stoi(str_input);
			}
			catch (std::logic_error)
			{
				failFlag = true;
			}			
			failFlag |= !((input >= limits.first) && (input <= limits.second));

		} while (failFlag);

		return input;
	}

	std::string inputString(std::string text)
	{
		std::string input{};
		do
		{
			std::cout << text;
			std::cin.clear();			

			std::cin >> input;
		} while (std::cin.fail());

		return input;
	}

	void dash(int count)
	{
		std::cout << '\n' << std::string('-', count) << std::endl;
	}
		
};