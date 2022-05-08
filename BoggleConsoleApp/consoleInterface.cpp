#pragma once

#include "consoleInterface.h"

#include <iostream>
#include <iomanip> // std::setw, std::setfill
#include <ios> // std::left, std::right
#include <ctime>
#include <Windows.h>
#include <thread>

using namespace std;


static int playingTimeInMinutes = 2;

static void runTimer(bool* timerOff);
static void addNewEmptyLine(void);
static void displayGameHelp(void);
static void updateGameTime(void);

/***************************************************************************************************/
void displayGameHeader(void)
{
	addNewEmptyLine();
	cout << "\t" << "W E L C O M E   T O  T H E  G A M E ** B O G G L E **" << endl;
	addNewEmptyLine();
}

/***************************************************************************************************/
int getNbrOfPlayer(void)
{
	addNewEmptyLine();
	string strValue;
	int m_nbrOfPlayer = 0;
	cout << "\t" << "Enter the number of player of the game..." << endl;
	cout << "\t" << ">>";
	getline(cin, strValue);
	m_nbrOfPlayer = stoi(strValue);
	return m_nbrOfPlayer;
}

/***************************************************************************************************/
string getPlayerName(int const playerNbr)
{
	addNewEmptyLine();
	string name;
	cout << "\t" << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	cout << "\t" << "Enter the name of the player " << playerNbr << endl;
	cout << "\t" << ">>";
	getline(cin, name);
	return name;
}

/***************************************************************************************************/
void displayGameHelp(void)
{
	addNewEmptyLine();
	cout << "\t" << "Game Help: " << endl;
	cout << "\t" << "=== Game Rules ===" << endl;
	cout << "\t" << "\t" << "1- The game uses a fixed board size of " << NBR_OF_ROWS << "x" << NBR_OF_COLUMNS <<"." << endl;
	cout << "\t" << "\t" << "2- Words must be a minimum of " << WORD_LENGHT_MIN << " characters." << endl;
	cout << "\t" << "\t" << "3- Each die must not be used more than once per word." << endl;
	cout << "\t" << "\t" << "4- Words can only be constructed from the letters of sequentially adjacent dice." << endl;
	cout << "\t" << "\t" << "4-1) e.g. those horizontally, vertically, and diagonally neighbouring the current one." << endl;
	cout << "\t" << "\t" << "5- The full game rules: https://en.wikipedia.org/wiki/Boggle#Rules." << endl;
	cout << "\t" << "=== Game Instructions ===" << endl;
	cout << "\t" << "\t" << "1- Enter a character by giving the number placed before each character." << endl;
	cout << "\t" << "\t" << "2- All number shall be separated by a blanc space." << endl;
	cout << "\t" << "\t" << "3- The game time is: " << playingTimeInMinutes <<" minutes." << endl;
	cout << "\t" << "\t" << "4- The game can be stopped in 2 ways:" << endl;
	cout << "\t" << "\t" << "4-1) The player press \"q\" to quit the game, OR..." << endl;
	cout << "\t" << "\t" << "4-2) The game stop automatically with a message when the timer exceeded." << endl;
	cout << "\t" << "\t" << "5- Press \"ENTER\" to validate a command." << endl;
	cout << "\t" << "=== Example ===" << endl;
	cout << "\t" << "1[H] - 12[A] - 8[L] - 5[L] - 9[O]";
	cout << "=> To select \"HALLO\", give \"1 12 8 5 9\", and press ENTER." << endl;
}

/***************************************************************************************************/
bool isPlayerReady(void)
{
	string opt;
	bool inputValid = false;

	do
	{
		addNewEmptyLine();
		cout << "\t" << "Choose one of the following options:" << endl;
		cout << "\t" << "\t" << "Option 1: Enter \"p\" to start playing." << endl;
		cout << "\t" << "\t" << "Option 2: Enter \"q\" to quit the game." << endl;
		cout << "\t" << "\t" << "Option 3: Enter \"h\" to show the help." << endl;
		cout << "\t" << ">>";
		getline(cin, opt);

		if (opt == "h")
		{
			displayGameHelp();
		}
		else if ((opt == "p") || (opt == "q"))
		{
			inputValid = true;
		}

	} while (!inputValid);

	return ((opt == "p") ? true : false);
}

/***************************************************************************************************/
void displayGameBoard(map<int, Dice> const& matrix)
{
	addNewEmptyLine();
	addNewEmptyLine();
	int col = 0;
	for (map<int, Dice>::const_iterator it = matrix.begin(); it != matrix.end(); ++it)
	{
		if (col < NBR_OF_COLUMNS)
		{
			if (col == 0)
			{
				cout << "\t" << setw(2) << right << setfill(' ')
					<< it->first << "[" << it->second.value << "]";
			}
			else
			{
				cout << "  " << setw(2) << right << setfill(' ')
					<< it->first << "[ " << it->second.value << " ]";
			}
			col++;
		}
		else
		{
			col = 0;
			addNewEmptyLine();
			cout << "\t" << setw(2) << right << setfill(' ')
				<< it->first << "[" << it->second.value << "]";
			col++;
		}
	}
	addNewEmptyLine();
}

/***************************************************************************************************/
vector<string> getPlayerInput(void)
{
	vector<string> playerInputs;
	string input = "";
	bool timerOff = false;
	bool stop = false;
	thread t1(runTimer, &timerOff);
	do
	{
		if ((!input.empty()) && isUserInputValid(input))
		{
			playerInputs.push_back(input);
		}
		cout << "\t" << ">>";
		getline(cin, input);
		if ((input == "q") || timerOff)
		{
			stop = true;
		}
	} while (!stop);
	timerOff = true;
	t1.join();

	return playerInputs;
}

/***************************************************************************************************/
void displayWinner(Player* m_winner)
{
	addNewEmptyLine();
	if (m_winner != NULL)
	{
		cout << "\t" << "Congratulations : The m_winner of the game is";
		cout << "\t" << "\" " << m_winner->name << " \"" << ", with the score: " << m_winner->score << endl;
	}
	else
	{
		cout << "\t" << "Sorry : Nobody won the party" << endl;
	}
}

/***************************************************************************************************/
void displayExitGameTxt(void)
{
	addNewEmptyLine();
	cout << "\t" << "T H A N K  Y O U  A N D  G O O D  B Y E !" << endl;
}

void displayChangePlayerName(void)
{
	cout << "\t" << "Oops!! A player with the same name already exists. Please enter a different name." << endl;
}

/***************************************************************************************************/
void displayGameTime(void)
{
	string opt;

	addNewEmptyLine();
	cout << "\t" << "The actual playing time is " << playingTimeInMinutes << " minute(s)." << endl;
	cout << "\t" << "Press \"t\" to change this time, otherwise this step will be skipped ." << endl;
	cout << "\t" << ">>";
	getline(cin, opt);

	if (opt == "t")
	{
		updateGameTime();
		cout << "\t" << "The actual playing time is *now* " << playingTimeInMinutes << " minute(s)." << endl;
	}
}

// STATIC FUNCTIONS

/***************************************************************************************************/
static void runTimer(bool* timerOff)
{
	int gameTimeInSec = playingTimeInMinutes * 60;
	while ((gameTimeInSec-- >= 0) && (!(*timerOff))) {
		Sleep(1000);
	}
	cout << endl << "\t" << "Timer off !! >> Please press \'ENTER\'" << endl;
	*timerOff = true;
}

/***************************************************************************************************/
static void addNewEmptyLine(void)
{
	cout << "\n" << endl;
}

/***************************************************************************************************/
static void updateGameTime(void)
{
	addNewEmptyLine();
	string strValue;
	int m_nbrOfPlayer = 0;
	cout << "\t" << "Enter the new playing time in minutes..." << endl;
	cout << "\t" << ">>";
	getline(cin, strValue);
	playingTimeInMinutes = stoi(strValue);
	cout << "\t" << "Playing time successfully updated." << endl;
}
