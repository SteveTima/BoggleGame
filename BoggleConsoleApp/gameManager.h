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
	void setGameTime(int timeInMinute);
	int getGameTime(void);
private:
	std::map<char, std::vector<std::string>> m_wordsDict;
	int m_nbrOfPlayer;
	Player *m_winner;
	std::vector<Player> m_gamePlayers;
};