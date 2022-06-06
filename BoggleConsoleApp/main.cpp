#include <iostream>

#include "gameManager.h"

using namespace std;



int main()
{
	GameManager newGame = GameManager();
	if (newGame.initGame())
	{
		newGame.startGame();
		newGame.stopGame();
	}
	else
	{
		cout << "Failed to load " << getWordsDictDatafilePath() << endl;
		cin.get();
	}
	return 0;
}

