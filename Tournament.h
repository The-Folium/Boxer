#pragma once
#define NOMINMAX
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <windows.h>
#include <MMSystem.h>
#include "Boxer.h"
#include <fstream>

extern Logger Log;
extern Settings settings;

class Tournament
{
public:
	std::vector<Boxer> boxerArray;
	size_t groupSize;
	std::ifstream boxerFile;

public:	
	
	int loadBoxers();
	void conduct();
	void addHumanPlayer(Boxer boxer);
	void showArrayState();
	int getComputerPlayerCount();
	bool isNaturalPowerOf2();
	std::pair<unsigned int, unsigned int> correction();
	void showPlayerList();
	void deleteBoxer(size_t index);
public: //MAKE THIS PRIVATE
	void kick(Boxer& whoKicks, Boxer& whoGets);
	bool fight(Boxer& boxer1, Boxer& boxer2);
	
	void round();
};