#pragma once

#include "gameManager.h"

using namespace std;

/***************************************************************************************************/
GameManager::GameManager()
{
	m_nbrOfPlayer = 0;
	m_winner = NULL;
	m_wordsDict = createEmptyDictionary();
}

/***************************************************************************************************/
bool GameManager::initGame(void)
{
	string m_wordsDictPath = getWordsDictDatafilePath();
	return fillDictionary(m_wordsDictPath, m_wordsDict);
}

/***************************************************************************************************/
void GameManager::startGame(void)
{
	displayGameHeader();
	displayGameTime();
	m_nbrOfPlayer = getNbrOfPlayer();
	if (m_nbrOfPlayer <= 0)
	{
		return;
	}

	for (int i = 0; i < m_nbrOfPlayer; i++)
	{
		Player newPlayer = Player();

		do
		{
			newPlayer.name = getPlayerName(i + 1);

		} while (nameExists(newPlayer.name));
		
		if (!isPlayerReady())
		{
			m_gamePlayers.push_back(newPlayer);
			continue; // the player exit the game
		}
		newPlayer.playerWords = play();
		newPlayer.score = getScore(newPlayer.playerWords, m_wordsDict);
		m_gamePlayers.push_back(newPlayer);
	}
}

/***************************************************************************************************/
bool GameManager::nameExists(string newName)
{
	int const actualPlayerLen = (int) m_gamePlayers.size();
	for (int i = 0; i < actualPlayerLen; i++)
	{
		if (m_gamePlayers[i].name == newName)
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
	displayWinner(m_winner);
	displayExitGameTxt();
}

/***************************************************************************************************/
void GameManager::setGameWinner()
{
	m_winner = &m_gamePlayers[0];
	for (int i = 1; i < m_nbrOfPlayer; i++)
	{
		if (m_gamePlayers[i].score > m_winner->score)
		{
			m_winner = &m_gamePlayers[i];
		}
	}
	if (m_winner->score == 0)
	{
		m_winner = NULL;
	}
}

