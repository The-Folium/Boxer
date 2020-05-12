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
	static constexpr unsigned char CONSOLE{ 0b0000'0001 };
	static constexpr unsigned char FILE{ 0b0000'0010 };
		
		
	void saveLog()
	{		
		logFile.close();		
	}

	void newLogFile(const std::string& path)
	{
		if (logFile.is_open()) { logFile.close(); }
		logFile.open(path);
	}

	void print(unsigned char logFlag, const std::string& text)
	{
		if (logFlag & CONSOLE){ std::cout << text; }
		if (logFlag & FILE) { logFile << text; }
	}

	void nextLine(unsigned char logFlag, int count = 1)
	{
		for (int i{ 0 }; i < count; ++i)
		{
			print(logFlag, "\n");
		}
	}
		
	void header(unsigned char logFlag, const std::string& text, const char ch)
	{
		std::string dash(text.length(), ch);
		if (logFlag & CONSOLE) { std::cout << text << '\n' << dash << '\n'; }
		if (logFlag & FILE) { logFile << text << '\n' << dash << '\n'; }
	}

	void wait()
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin.get();
	}

	int inputInt(const std::string& text, std::pair<int, int> limits)
	{
		int input{1};		
		std::cin.clear();
		bool failFlag{ false };
		do
		{			
			if (failFlag)
			{
				print(CONSOLE, "Incorrect input. Try again.\n");
			}
			print(CONSOLE, text);
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

	std::string inputString(const std::string& text)
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
};