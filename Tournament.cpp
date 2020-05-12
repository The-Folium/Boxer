#include "Tournament.h"


int Tournament::loadBoxers()
{
	boxerFile.open(settings.computerPlayersFilePath);
	if (boxerFile.good())
	{
		Boxer boxer;
		boxerArray.clear();
		while (boxerFile >> boxer.name >> boxer.last_name >> boxer.age)
		{
			boxer.isHumanPlayer = false;
			boxerArray.push_back(boxer);
		}
		boxerFile.close();
		settings.isBoxerFileValid = true;
		return boxerArray.size();
	}
	else
	{
		boxerFile.close();
		settings.isBoxerFileValid = false;
		return -1;//error code
	}
}

void Tournament::conduct()
{
	//test boxerArray size
	groupSize = boxerArray.size();
	int roundCounter{ 0 };
	while (groupSize > 1)
	{
		++roundCounter;
		Log.toConsole("Round " + std::to_string(roundCounter) + "      Group size: " + std::to_string(groupSize) + '\n');

		round();
		groupSize >>= 1;
	}
}

void Tournament::addHumanPlayer(Boxer boxer)
{
	boxerArray.push_back(boxer);
}

void Tournament::showArrayState()
{
	for (size_t i{ 0 }; i < boxerArray.size(); ++i)
	{
		Log.toConsole(boxerArray[i].name + " < ");
	}
	Log.nextLineToConsole();
}

int Tournament::getComputerPlayerCount()
{
	return boxerArray.size();
}

bool Tournament::isNaturalPowerOf2()
{
	bool flag{ true };
	unsigned int temp{ boxerArray.size() };
	while (temp > 1)
	{		
		if (temp % 2) { flag = false; }
		temp >>= 1;
	};
	return flag;
}

std::pair<unsigned int, unsigned int> Tournament::correction()
{
	unsigned int temp{1};
	auto currentArraySize{ boxerArray.size() };
	while (temp < currentArraySize)
	{
		temp <<= 1;
	}
	unsigned int up{ temp - currentArraySize };
	temp >>= 1;
	unsigned int down{ currentArraySize - temp};
	return std::make_pair(down, up);
}


void Tournament::showPlayerList()
{
	for (size_t index{ 0 }; index < boxerArray.size(); ++index)
	{
		Boxer& currentBoxer = boxerArray[index];
		std::string isHumanComment{};
		if (currentBoxer.isHumanPlayer) { isHumanComment = " *HUMAN*"; }

		std::string spaces(32 - currentBoxer.getFullName().length() - isHumanComment.length(), ' ');
		if (index % 2 == 1) { spaces = "\n"; }
		Log.toConsole(std::to_string(index + 1) + ". " + currentBoxer.getFullName() + isHumanComment + spaces);
	}
	Log.nextLineToConsole();
}

void Tournament::deleteBoxer(size_t index)
{
	if (boxerArray[index].isHumanPlayer) { --settings.humanPlayerCounter; }
	boxerArray.erase(boxerArray.begin() + index);
}

void Tournament::kick(Boxer& whoKicks, Boxer& whoGets)
{
	int damage{ 0 };
	if (whoKicks.getTarget() != whoGets.getProtectingZone())
	{
		damage = bodyPartPoints(whoKicks.getTarget());
		whoGets.hp -= damage;
	}

	//displaying results
	if (damage == 0)
	{
		Log.toConsole("Punch has been blocked!\n");
	}
	else
	{
		Log.toConsole("Punch successful! " + whoGets.getFullName() + " lost " + std::to_string(damage) + " HP.\n");
	}
}

bool Tournament::fight(Boxer& boxer1, Boxer& boxer2)
{
	if (settings.soundFlag) { PlaySound(TEXT("bell.wav"), NULL, SND_FILENAME | SND_ASYNC); }

	Boxer* p_boxer1{ &boxer1 };
	Boxer* p_boxer2{ &boxer2 };
	bool Boxer1Wins{ true };
	while (true)
	{
		
		p_boxer1->setTarget(p_boxer1->generateBodyPart("Where wanna punch your opponent?\n"));
		Log.toConsole(p_boxer1->getFullName() + " is about to punch " + p_boxer2->getFullName() +
				" in his " + bodyPartToString(p_boxer1->getTarget()));
		
		p_boxer2->setProtectingZone(p_boxer2->generateBodyPart("Which bodypart do you wanna protect?\n"));
		Log.toConsole(p_boxer2->getFullName() + " protects his " + bodyPartToString(p_boxer2->getProtectingZone()));
		
		
		kick(*p_boxer1, *p_boxer2);
		if (!p_boxer2->isAlive())
		{
			Log.toConsole(p_boxer2->getFullName() + " has been defeated! " + p_boxer1->getFullName() + " wins!\n");
			p_boxer1->hp = p_boxer2->hp = 100; //restoring hp after fight;
			return (Boxer1Wins);			
		}
		p_boxer1->printStatus();
		p_boxer2->printStatus();
		Boxer1Wins = !Boxer1Wins;
		
		std::swap(p_boxer1, p_boxer2);
		std::cin.clear();
		std::cin.get();
	}	

}


void Tournament::round()
{
	const size_t groupNumber{ boxerArray.size() / groupSize };
	for (unsigned int groupCounter{ 0 }; groupCounter < groupNumber; ++groupCounter)
	{
		size_t left_index{ groupCounter * groupSize };
		size_t right_index{ left_index + groupSize - 1 };

		while (left_index < right_index)
		{
			if (fight(boxerArray[left_index], boxerArray[right_index])) //fight is true if left boxer wins
			{
				std::swap(boxerArray[left_index], boxerArray[right_index]);
			}
			++left_index;
			--right_index;
		}
		Log.toConsole(std::to_string(groupCounter) + ":");
		showArrayState();
	}
}