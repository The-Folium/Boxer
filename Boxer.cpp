#include "Boxer.h"


Boxer::Boxer(const std::string& name_init,const std::string& last_name_init, unsigned int age_init, bool isHuman) :
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
	name{},
	last_name{},
	age{},
	hp{ 100 },
	target{ BodyPart::NONE },
	protectingZone{ BodyPart::NONE },
	isHumanPlayer{ false }
{
}

int Boxer::getRandom(int min, int max)
{
	std::uniform_int_distribution<int> value{ min, max };
	return value(mersenne);
}

BodyPart Boxer::generateBodyPart(const std::string& prompt)
{
	if (isHumanPlayer)
	{
		Log.print(Logger::CONSOLE,prompt);
		std::string availableParts{};
		for (int i{ 1 }; i <= static_cast<int>(settings.level); ++i)
		{
			availableParts += (std::to_string(i) + " - " + bodyPartToString(bodyPartByNumber(i)) + "   ");
		}
		Log.print(Logger::CONSOLE,"Select body part:\n" + availableParts + '\n');
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

std::string Boxer::getFullName(bool aligned)
{
	std::string fullName{ name + ' ' + last_name };
	if (aligned) { fullName += std::string(settings.maxBoxerNameLength - fullName.length() + 3, ' '); }
	return fullName;
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
	else if (hp > 0)  { conclusion = "Death is near..."; }
	Log.print(Logger::CONSOLE,getFullName() + "'s HP: " + std::to_string(hp) + "   " + conclusion + '\n');
}

void Boxer::makeHuman()
{
	isHumanPlayer = true;
}

std::mt19937 Boxer::mersenne(static_cast<std::mt19937::result_type>(std::time(nullptr)));