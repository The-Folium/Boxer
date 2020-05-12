#include "Game.h"
enum MainMenuOption
{
	START = 1, DIFFICULTY, BOXER_FILE, LOG_FILE, ADD_HUMAN, DELETE_PLAYER, SOUND, EXIT
};

enum HumanMenuOption
{
	FROM_FILE = 1, CREATE, RETURN
};

enum CreateMenuOption
{
	NAME = 1, LAST_NAME, AGE, CONFIRM, CANCEL
};



void Game::run()
{
	std::string boxerFileComment{};
	int boxerFileState{};	
	while (true)
	{
		Log.nextLineToConsole(2);		
		Menu mainMenu("MAIN MENU");
		
		if (settings.needReload) 
		{ 
			boxerFileState = tournament.loadBoxers();			
			if (boxerFileState == -1) { boxerFileComment = "File Not Found"; }
			else { boxerFileComment = std::to_string(boxerFileState) + " computer boxers loaded"; }
			settings.needReload = false;
		}

		std::string tournamentStateComment;
		bool isReady{ true };
		if (settings.humanPlayerCounter + tournament.getComputerPlayerCount() < 2) { tournamentStateComment = "Need more players"; isReady = false; }
		if (!tournament.isNaturalPowerOf2())
		{
			auto correction {tournament.correction()};			
			tournamentStateComment = "Add "+std::to_string(correction.second) + " OR Delete " + std::to_string(correction.first); isReady = false; 
		}
		else
		{
			tournamentStateComment = "We have " + std::to_string(tournament.boxerArray.size()) + " boxers!";
		}
		std::string readyStatusComment{ isReady ? "READY" : "ERROR:" };

		std::string soundStateComment{ settings.soundFlag ? "ON" : "OFF" };

		mainMenu.addOption("Start Tournament      " + readyStatusComment + "  " + tournamentStateComment);
		mainMenu.addOption("Difficulty:           " + settings.getDifficultyAsString());
		mainMenu.addOption("Computer Player File: \"" + settings.computerPlayersFilePath + "\"   " + boxerFileComment);
		mainMenu.addOption("Tournament Log File:  \"" + settings.logFilePath + "\"");
		mainMenu.addOption("Add Human Player:     " + std::to_string(settings.humanPlayerCounter) + " already participates");
		mainMenu.addOption("Delete Player");
		mainMenu.addOption("Sound:                " + soundStateComment);
		mainMenu.addOption("Exit");

		MainMenuOption option{ static_cast<MainMenuOption>(mainMenu.askOption()) };
		switch (option)
		{
			case(START):
			{
				if (isReady) tournament.conduct(); break;
			}
			case(DIFFICULTY):
			{
				Menu difficultyMenu("DIFFICULTY LEVEL");
				difficultyMenu.addOption("EASY:    3 body parts");
				difficultyMenu.addOption("MEDIUM:  4 body parts");
				difficultyMenu.addOption("HARD:    5 body parts");

				settings.level = static_cast<Settings::DifficultyLevel> (difficultyMenu.askOption() + 2);
				break;
			}

			case(BOXER_FILE):
			{
				std::string newFileName{ Log.inputString("Enter new BOT filename (\"C\" - to Cancel): ") };
				if (newFileName != "C" && newFileName != "c") { settings.computerPlayersFilePath = newFileName; }
				settings.needReload = true;
				break;
			}

			case(LOG_FILE):
			{
				std::string newFileName{ Log.inputString("Enter new LOG filename (\"C\" - to Cancel): ") };
				if (newFileName != "C" && newFileName != "c") { settings.logFilePath = newFileName; }
				Log.newLogFile(settings.logFilePath);
				break;
			}

			case(ADD_HUMAN):
			{
				Menu addHumanMenu("ADD NEW HUMAN PLAYER");
				std::string chooseFromLoadedComment{(settings.isBoxerFileValid && (tournament.boxerArray.size() >=1)) ? "AVAILABLE" : "N/A. Check computer players file."};
				addHumanMenu.addOption("Select from loaded players:  " + chooseFromLoadedComment);
				addHumanMenu.addOption("Create new human player");
				addHumanMenu.addOption("Return");

				HumanMenuOption option{ static_cast<HumanMenuOption>(addHumanMenu.askOption()) };
				switch (option)
				{
					case(FROM_FILE):
					{
						tournament.showPlayerList();

						bool choiceMade{ false };
						while (!choiceMade)
						{
							int newHumanIndex{ Log.inputInt("[0 - to return, 1.." + std::to_string(tournament.boxerArray.size()) + " - to choose your character]: ",
															std::make_pair(0, tournament.boxerArray.size())) };
							if (newHumanIndex)
							{
								Boxer& currentBoxer{ tournament.boxerArray[newHumanIndex-1] };
								if (currentBoxer.isHumanPlayer)
								{
									Log.toConsole("Sorry, " + currentBoxer.getFullName() + " is a human Player already. Please, try another one.");
								}
								else
								{
									currentBoxer.makeHuman();
									Log.toConsole(currentBoxer.getFullName() + " is a NEW human Player now!");
									++settings.humanPlayerCounter;
									choiceMade = true;
								}								
							}
							if (!newHumanIndex) { choiceMade = true; }
						}
						break;
					}
					case(CREATE):
					{
						Boxer newBoxer("No_Name", "No_Last_Name", 0, true);
						bool confirmFlag{ false };
						while (!confirmFlag)
						{
							Menu createMenu("CREATE NEW HUMAN BOXER");
							createMenu.addOption("Name        :" + newBoxer.name);
							createMenu.addOption("Last Name   :" + newBoxer.last_name);
							createMenu.addOption("Age         :" + std::to_string(newBoxer.age));
							createMenu.addOption("Confirm");
							createMenu.addOption("Cancel");

							CreateMenuOption option{ static_cast<CreateMenuOption>(createMenu.askOption()) };

							switch (option)
							{
								case(NAME):
								{
									std::string newName{ Log.inputString("Enter new NAME (\"C\" - to Cancel): ") };
									if (newName != "C" && newName != "c") { newBoxer.name = newName; }									
									break;
								}
								case(LAST_NAME):
								{
									std::string newLastName{ Log.inputString("Enter new LAST NAME (\"C\" - to Cancel): ") };
									if (newLastName != "C" && newLastName != "c") { newBoxer.last_name = newLastName; }
									break;
								}
								case(AGE):
								{
									int newAge{ Log.inputInt("[0 - to return, 1..99 - ]: ",	std::make_pair(0, 99)) };
									if (newAge) { newBoxer.age = newAge; }
									break;
								}
								case(CONFIRM):
								{
									confirmFlag = true;
									tournament.boxerArray.push_back(newBoxer);
									++settings.humanPlayerCounter;
									Log.toConsole(newBoxer.getFullName() + " is a NEW human Player now!");
									break;
								}
								default: break;
							}
						}
						break;
					}
					
				}
				break;
			}

			case (DELETE_PLAYER):
			{
				tournament.showPlayerList();
				
				int deletePlayerIndex{ Log.inputInt("[0 - to return, 1.." + std::to_string(tournament.boxerArray.size()) + " - to choose your character]: ",
													std::make_pair(0, tournament.boxerArray.size())) };
				if (deletePlayerIndex)
				{
						Log.toConsole(tournament.boxerArray[deletePlayerIndex-1].getFullName() + " has been deleted!");
						tournament.deleteBoxer(deletePlayerIndex-1);											
				}			
				
				break;
			}

			case(SOUND):
			{
				settings.soundFlag = !settings.soundFlag;
				break;
			}

			default:
			{
				break;
			}
		}
	}
}
