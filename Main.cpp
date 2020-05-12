
#include <utility>
#include <string>
#include "Tournament.h"
#include "Log.h"
#include "Game.h"

Logger Log("log.txt");
Settings settings;

int main()
{
	Game game;
	game.run();
	
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.get();
}