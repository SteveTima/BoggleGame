#pragma once

#include "consoleInterface.h"

class GameManager
{
public:
	GameManager(void);
	bool initGame(void);
	void startGame(void);
	void stopGame(void);
private:
	std::vector<InputString> play(void);
	void setGameWinner();
	bool nameExists(std::string newName);
private:
	std::map<char, std::vector<std::string>> wordsDict;
	int nbrOfPlayer;
	Player *winner;
	std::vector<Player> gamePlayers;
	int gameTimeMinute;
};