#include "Boxer.h"


Boxer::Boxer(std::string name_init, std::string last_name_init, unsigned int age_init, bool isHuman) :
	name{ name_init },
	last_name{ last_name_init },
	age{ age_init },
	isHumanPlayer{ isHuman },
	hp{ 100 },
	target{BodyPart::NONE},
	protectingZone{ BodyPart::NONE }
	
{
}

Boxer::Boxer():
	hp{ 100 },
	target{ BodyPart::NONE },
	protectingZone{ BodyPart::NONE }
{
}

int Boxer::getRandom(int min, int max)
{
	std::uniform_int_distribution<int> value{ min, max };
	return value(mersenne);
}

BodyPart Boxer::generateBodyPart(std::string prompt)
{
	if (isHumanPlayer)
	{
		Log.toConsole(prompt);
		std::string availableParts{};
		for (int i{ 1 }; i <= static_cast<int>(settings.level); ++i)
		{
			availableParts += (std::to_string(i) + " - " + bodyPartToString(bodyPartByNumber(i)) + "   ");
		}
		Log.toConsole("Select body part:\n" + availableParts + '\n');
		int input{ Log.inputInt("Enter 1.." + std::to_string(static_cast<int>(settings.level)) + ":  ", std::make_pair(1, static_cast<int>(settings.level))) };
		return bodyPartByNumber(input);
	}

	else

	{
		return bodyPartByNumber(getRandom(1, static_cast<int>(settings.level)));
	}
	
	return BodyPart();
}

bool Boxer::isAlive()
{
	return hp > 0;
}

BodyPart Boxer::getTarget()
{
	return target;
}

void Boxer::setTarget(BodyPart part)
{
	target = part;
}

BodyPart Boxer::getProtectingZone()
{
	return protectingZone;
}

void Boxer::setProtectingZone(BodyPart part)
{
	protectingZone = part;
}

std::string Boxer::getFullName()
{
	return name + ' ' + last_name;
}

void Boxer::printStatus()
{
	std::string conclusion;
		 if (hp > 90) { conclusion = "No doubt. Perfect health."; }
	else if (hp > 80) { conclusion = "Our hero is still going strong!"; }
	else if (hp > 70) { conclusion = "First blood. Just setting him off!"; }
	else if (hp > 60) { conclusion = "Merciless is his middle name. "; }
	else if (hp > 50) { conclusion = "Aaagh!!! His spirit is far from being broken!"; }
	else if (hp > 40) { conclusion = "There's rage in his veins! Beware!"; }
	else if (hp > 30) { conclusion = "There's nothing more dangerous than a wounded beast!"; }
	else if (hp > 20) { conclusion = "Furious but weakening."; }
	else if (hp > 10) { conclusion = "Highly severe injuries."; }
	else if (hp > 0) { conclusion = "Death is near..."; }
	Log.toConsole(getFullName() + "'s HP: " + std::to_string(hp) + "   " + conclusion);
}

void Boxer::makeHuman()
{
	isHumanPlayer = true;
}

std::mt19937 Boxer::mersenne(static_cast<std::mt19937::result_type>(std::time(nullptr)));