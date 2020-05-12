#pragma once
#include <string>

struct Settings
//holds all data we want to freely access everywhere
{
	enum DifficultyLevel
	{
		Easy=3, Medium, Hard
	};

	DifficultyLevel level{ Easy };
	bool soundFlag{ false };
	int humanPlayerCounter{ 0 };

	bool isBoxerFileValid{ false };
	bool needReload{ true };
	bool humanIsFighting{ false };

	size_t maxBoxerNameLength{ 0 };	//keeps track of the longest boxer name. it is used in formatting

	std::string computerPlayersFilePath{ "boxers.txt" };
	std::string logFilePath{ "log.txt" };

	std::string getDifficultyAsString()
	{
		switch (level)
		{
		case(Easy): return "EASY (3 zones)";
		case(Medium): return "MEDIUM (4 zones)";
		case(Hard): return "HARD (5 zones)";
		}
		return "";
		
	}
};