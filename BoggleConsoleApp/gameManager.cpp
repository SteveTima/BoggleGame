#pragma once

#include "gameManager.h"

using namespace std;

/***************************************************************************************************/
GameManager::GameManager()
{
	nbrOfPlayer = 0;
	gameTimeMinute = 0;
	winner = NULL;
	wordsDict = createEmptyDictionary();
}

/***************************************************************************************************/
bool GameManager::initGame(void)
{
	string wordsDictPath = getWordsDictDatafilePath();
	return fillDictionary(wordsDictPath, wordsDict);
}

/***************************************************************************************************/
void GameManager::startGame(void)
{
	displayGameHeader();
	nbrOfPlayer = getNbrOfPlayer();
	if (nbrOfPlayer <= 0)
	{
		return;
	}

	for (int i = 0; i < nbrOfPlayer; i++)
	{
		Player newPlayer = Player();

		do
		{
			newPlayer.name = getPlayerName(i + 1);

		} while (nameExists(newPlayer.name));
		
		if (!isPlayerReady())
		{
			gamePlayers.push_back(newPlayer);
			continue; // the player exit the game
		}
		newPlayer.playerWords = play();
		newPlayer.score = getScore(newPlayer.playerWords, wordsDict);
		gamePlayers.push_back(newPlayer);
	}
}

/***************************************************************************************************/
bool GameManager::nameExists(string newName)
{
	int const actualPlayerLen = (int) gamePlayers.size();
	for (int i = 0; i < actualPlayerLen; i++)
	{
		if (gamePlayers[i].name == newName)
		{
			displayChangePlayerName();
			return  true;
		}
	}
	return  false;
}

/***************************************************************************************************/
vector<InputString> GameManager::play(void)
{
	vector<string> playerListWords;
	vector<InputString> playerListCustomWords;
	vector<InputString> playerListCustomWordsValid;
	map<int, Dice> newMap;

	newMap = createMapOfDiesValues();
	displayGameBoard(newMap);
	playerListWords = getPlayerInput();
	playerListCustomWords = stringToPlayerString(playerListWords, newMap);
	playerListCustomWordsValid = validate(playerListCustomWords);

	newMap.clear();
	playerListWords.clear();
	playerListCustomWords.clear();
	return playerListCustomWordsValid;
}

/***************************************************************************************************/
void GameManager::stopGame(void)
{
	setGameWinner();
	displayWinner(winner);
	displayExitGameTxt();
}

/***************************************************************************************************/
void GameManager::setGameWinner()
{
	winner = &gamePlayers[0];
	for (int i = 1; i < nbrOfPlayer; i++)
	{
		if (gamePlayers[i].score > winner->score)
		{
			winner = &gamePlayers[i];
		}
	}
	if (winner->score == 0)
	{
		winner = NULL;
	}
}
