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
	void conduct();//runs tournament;
	void addHumanPlayer(const Boxer& boxer);
	void printRankTable(unsigned char logFlag);	//prints to log current boxerArray state
	bool isNaturalPowerOf2();	//tests whether we've got valid nuber of boxers or not
	std::pair<unsigned int, unsigned int> correction();	//yields how many boxers we have to add/delete to rich appropriate number of competitors
	void showPlayerList();	//prints to log current player list
	void deleteBoxer(size_t index);	
	size_t getBoxerNumber();		//just returns boxerArray.size(). 	
	void resetWins();

private:
	void kick(Boxer& whoKicks, Boxer& whoGets);
	bool fight(Boxer& boxer1, Boxer& boxer2);	
	void round();	
};