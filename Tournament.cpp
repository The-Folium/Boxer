#include "Tournament.h"

int Tournament::loadBoxers()
{
	boxerFile.open(settings.computerPlayersFilePath);
	settings.maxBoxerNameLength = 0;
	if (boxerFile.good())
	{
		Boxer boxer;
		boxerArray.clear();
		while (boxerFile >> boxer.name >> boxer.last_name >> boxer.age)
		{
			boxer.isHumanPlayer = false;
			boxerArray.push_back(boxer);
			size_t currentNameLength{ boxer.getFullName().length() };
			if (currentNameLength > settings.maxBoxerNameLength) { settings.maxBoxerNameLength = currentNameLength; }

		}
		boxerFile.close();
		settings.isBoxerFileValid = true;
		return getBoxerNumber();
	}
	else
	{
		boxerFile.close();
		settings.isBoxerFileValid = false;
		return -1;//error code
	}
}

size_t Tournament::getBoxerNumber()
{
	return boxerArray.size();
}

void Tournament::resetWins()
{
	for (auto& boxer : boxerArray)
	{
		boxer.wins = 0;
	}
}

void Tournament::conduct()
{
	Log.newLogFile(settings.logFilePath);
	Log.print(Logger::FILE, "Tournament begins: " + std::to_string(getBoxerNumber()) + " boxers participate\n");
	
	groupSize = getBoxerNumber();
	int roundCounter{ 0 };

	while (groupSize > 1)
	{
		++roundCounter;
		Log.nextLine(Logger::CONSOLE | Logger::FILE, 2);
		
		Log.header(Logger::CONSOLE | Logger::FILE,"Round " + std::to_string(roundCounter) + "      Group size: " + std::to_string(groupSize),'*');

		round();
		groupSize >>= 1;
	}
	Log.nextLine(Logger::CONSOLE | Logger::FILE);
	printRankTable(Logger::CONSOLE | Logger::FILE);
	Log.saveLog();
	resetWins();
	Log.wait();
}

void Tournament::addHumanPlayer(const Boxer& boxer)
{
	boxerArray.push_back(boxer);
}

void Tournament::printRankTable(unsigned char logFlag)
{
	Log.header(logFlag, "Total Tournament Ranking", '=');
	Log.header(logFlag, "Place   Boxer  " + std::string(settings.maxBoxerNameLength + 2, ' ') + "Wins   Age\n",'-');
	for (size_t i{ 0 }; i < getBoxerNumber(); ++i)
	{
		std::string place{ std::to_string(i+1) };
		Log.print(logFlag,place + " : \t" + boxerArray[i].getFullName(true) + " \t" + std::to_string(boxerArray[i].wins) + "      " + std::to_string(boxerArray[i].age)+ "\n");
	}
	Log.nextLine(logFlag);
}


bool Tournament::isNaturalPowerOf2()
{
	bool flag{ true };
	unsigned int temp{ getBoxerNumber() };
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
	auto currentArraySize{ getBoxerNumber() };
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
	for (size_t index{ 0 }; index < getBoxerNumber(); ++index)
	{
		Boxer& currentBoxer = boxerArray[index];
		std::string isHumanComment{};
		if (currentBoxer.isHumanPlayer) { isHumanComment = " *HUMAN*"; }

		std::string spaces(32 - currentBoxer.getFullName().length() - isHumanComment.length(), ' ');
		if (index % 2 == 1) { spaces = "\n"; }
		Log.print(Logger::CONSOLE,std::to_string(index + 1) + ". " + currentBoxer.getFullName() + isHumanComment + spaces);
	}
	Log.nextLine(Logger::CONSOLE);
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
		if(settings.humanIsFighting) Log.print(Logger::CONSOLE,"Punch has been blocked!\n\n");
	}
	else
	{
		if (settings.humanIsFighting) Log.print(Logger::CONSOLE,"Punch successful! " + whoGets.getFullName() + " lost " + std::to_string(damage) + " HP.\n\n");
	}
	
}



bool Tournament::fight(Boxer& boxer1, Boxer& boxer2)
{
	settings.humanIsFighting = false;
	if (boxer1.isHumanPlayer || boxer2.isHumanPlayer) { settings.humanIsFighting = true; }
	if (settings.soundFlag && settings.humanIsFighting) { PlaySound(TEXT("bell.wav"), NULL, SND_FILENAME | SND_ASYNC); }
	
	
	Boxer* p_boxer1{ &boxer1 };
	Boxer* p_boxer2{ &boxer2 };
	bool Boxer1Wins{ true };
	while (true)
	{
		
		p_boxer1->setTarget(p_boxer1->generateBodyPart("\nWhere wanna punch your opponent?\n"));
		p_boxer2->setProtectingZone(p_boxer2->generateBodyPart("\nWhich bodypart do you wanna protect?\n"));

		if (settings.humanIsFighting) Log.print(Logger::CONSOLE,p_boxer1->getFullName() + " is about to punch " + p_boxer2->getFullName() +
				" in his " + bodyPartToString(p_boxer1->getTarget()) + '\n');
				
		if (settings.humanIsFighting) Log.print(Logger::CONSOLE,p_boxer2->getFullName() + " protects his " + bodyPartToString(p_boxer2->getProtectingZone()) + "\n");
		
		
		kick(*p_boxer1, *p_boxer2);
		if (!p_boxer2->isAlive())
		{
			Log.print(Logger::CONSOLE,"\n" + p_boxer2->getFullName() + " has been defeated! " + p_boxer1->getFullName() + " wins!\n");
			Log.print(Logger::FILE, "   WINNER: " + p_boxer1->getFullName() + "\n");
			++p_boxer1->wins;
			p_boxer1->hp = p_boxer2->hp = 100; //restoring hp after fight;

			return (Boxer1Wins);			
		}

		if (settings.humanIsFighting)
		{			
			p_boxer1->printStatus();
			p_boxer2->printStatus();
			Log.nextLine(Logger::CONSOLE);
		}

		Boxer1Wins = !Boxer1Wins;
		
		std::swap(p_boxer1, p_boxer2);
		
	}	

}


void Tournament::round()
{
	
	const size_t groupNumber{ getBoxerNumber() / groupSize };
	for (unsigned int groupCounter{ 0 }; groupCounter < groupNumber; ++groupCounter)
	{
		Log.print(Logger::CONSOLE,"\nGroup " + std::to_string(groupCounter + 1) + ": ");
		Log.nextLine(Logger::CONSOLE | Logger::FILE);
		size_t left_index{ groupCounter * groupSize };
		size_t right_index{ left_index + groupSize - 1 };

		std::string groupEnumeration{};
		for (size_t index{ left_index }; index <= right_index; ++index)
		{
			char separator{ (index == right_index) ? ' ' : ',' };
			groupEnumeration += (boxerArray[index].name + separator + ' ') ;			
		}
		Log.print(Logger::CONSOLE,groupEnumeration + "\n\n");

		while (left_index < right_index)
		{
			Boxer& boxer1{ boxerArray[left_index] };
			Boxer& boxer2{ boxerArray[right_index] };
			Log.print(Logger::CONSOLE | Logger::FILE, "  " + boxer1.getFullName(true) + "VS   " + boxer2.getFullName(true) + " : ");

			if (!fight(boxer1, boxer2)) //fight is true if first boxer wins and we don't swap elements in this case
			{
				std::swap(boxer1, boxer2); 
			}
						
			++left_index;
			--right_index;

		}
		
	}
		
}
