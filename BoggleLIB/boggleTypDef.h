#pragma once

#include <string>
#include <vector>

#define NBR_OF_COLUMNS			4
#define NBR_OF_ROWS				4
#define NBR_OF_SIDES_PER_DICE	6

// Dice Matrix definition
static char const DIE_MATRIX[(NBR_OF_ROWS * NBR_OF_COLUMNS)][NBR_OF_SIDES_PER_DICE] =
{
	{'E', 'T', 'U', 'K', 'N', 'O'},
	{'E', 'V', 'G', 'T', 'I', 'N'},
	{'D', 'E', 'C', 'A', 'M', 'P'},
	{'I', 'E', 'L', 'R', 'U', 'W'},
	{'E', 'H', 'I', 'F', 'S', 'E'},
	{'R', 'E', 'C', 'A', 'L', 'S'},
	{'E', 'N', 'T', 'D', 'O', 'S'},
	{'O', 'F', 'X', 'R', 'I', 'A'},
	{'N', 'A', 'V', 'E', 'D', 'Z'},
	{'E', 'I', 'O', 'A', 'T', 'A'},
	{'G', 'L', 'E', 'N', 'Y', 'U'},
	{'B', 'M', 'A', 'Q', 'J', 'O'},
	{'T', 'L', 'I', 'B', 'R', 'A'},
	{'S', 'P', 'U', 'L', 'T', 'E'},
	{'A', 'I', 'M', 'S', 'O', 'R'},
	{'E', 'N', 'H', 'R', 'I', 'S'}
};


struct Dice
{
	int row;
	int column;
	char value;
	Dice();
	Dice(int r, int c);
	Dice(char v);
	Dice(int r, int c, char v);
};

struct InputString
{
	std::string strValue;
	std::vector<Dice> dies;
	unsigned int score;
	InputString();
	InputString(std::string p_strValue);
	InputString(std::vector<Dice> p_dies, std::string p_strValue);
};


struct Player
{
	std::string name;
	std::vector<InputString> playerWords;
	unsigned int score;
	Player();
	Player(std::string p_name);
};

