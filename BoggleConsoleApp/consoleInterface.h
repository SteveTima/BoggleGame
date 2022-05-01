#pragma once

#include "../BoggleLIB/boggleConfig.h"
#include "../BoggleLIB/boggleValidation.h"

void displayGameBoard(std::map<int, Dice> const& matrix);
void displayWinner(Player* winner);
void displayExitGameTxt(void);
void displayGameHeader(void);
void displayChangePlayerName(void);

int getNbrOfPlayer(void);
bool isPlayerReady(void);
std::string getPlayerName(int const playerNbr);
std::vector<std::string> getPlayerInput(void);



