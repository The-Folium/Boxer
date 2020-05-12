#pragma once
#include <string>
#include <random>
#include <ctime>
#include "BodyPart.h"
#include "Settings.h"
#include "Log.h"

extern Logger Log;
extern Settings settings;

class Boxer
{
public:	
	int hp;
	std::string name;
	std::string last_name;
	unsigned int age;
	bool isHumanPlayer{ false };
	static std::mt19937 mersenne;

private:
	
	BodyPart target;
	BodyPart protectingZone;

public:
	Boxer(std::string name_init, std::string last_name_init, unsigned int age__init, bool isHuman);
	Boxer();
	int getRandom(int min, int max);
	BodyPart generateBodyPart(std::string prompt = "");
	bool isAlive();
	BodyPart getTarget();
	void setTarget(BodyPart part);
	BodyPart getProtectingZone();
	void setProtectingZone(BodyPart part);
	std::string getFullName();
	void printStatus();
	void makeHuman();
	
};