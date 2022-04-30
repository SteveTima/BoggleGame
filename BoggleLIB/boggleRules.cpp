#include "boggleRules.h"

#include <assert.h>

#include "boggleConfig.h"

using namespace std;

static std::vector<Dice> getListAdjacentDies(Dice const& dice);
static bool isDiceAdjancent(Dice const& nextDice, std::vector<Dice> const& listAdjacentDies);

/***************************************************************************************************/
bool checkCharLenght(string const& word)
{
	assert(!word.empty());
	bool retVal = true;
	if (word.length() < WORD_LENGHT_MIN)
	{
		retVal = false;
	}
	return retVal;
}

/***************************************************************************************************/
bool checkRedundancy(vector<Dice> const& listOfDice)
{
	vector<Dice> buffer;
	for (vector<Dice>::const_iterator it = listOfDice.begin(); it != listOfDice.end(); ++it)
	{
		if (buffer.empty())
		{
			buffer.push_back(*it);
		}
		else
		{
			for (vector<Dice>::const_iterator it2 = buffer.begin(); it2 != buffer.end(); ++it2)
			{
				if ((*it).column == (*it2).column && (*it).row == (*it2).row)
				{
					return true;
				}
			}
			buffer.push_back(*it);
		}
	}
	return false;
}

/***************************************************************************************************/
bool checkCharPositions(vector<Dice> const& listOfDice)
{
	vector<Dice> adjacentsPos;
	vector<Dice>::const_iterator dice = listOfDice.begin();
	adjacentsPos = getListAdjacentDies(*dice);

	for (++dice; dice != listOfDice.end(); ++dice)
	{
		if (!isDiceAdjancent((*dice), adjacentsPos))
		{
			return false;
		}
		adjacentsPos = getListAdjacentDies(*dice);
	}
	return true;
}

// STATIC FUNCTIONS

/***************************************************************************************************/
static vector<Dice> getListAdjacentDies(Dice const& dice)
{
	vector<Dice> ret_list;
	int x, y;
	int const maxNbrOfAdjacentChar = 8;
	int rowTab[maxNbrOfAdjacentChar] = { -1, 1,  0, 0, -1, 1,  1, -1 };
	int columnTab[maxNbrOfAdjacentChar] = { 0, 0, -1, 1, -1, 1, -1,  1 };
	for (int i = 0; i < maxNbrOfAdjacentChar; i++)
	{
		x = dice.row + rowTab[i];
		y = dice.column + columnTab[i];
		if ((x >= 0 && x < NBR_OF_ROWS) && (y >= 0 && y < NBR_OF_COLUMNS))
		{
			ret_list.push_back(Dice(x, y));
		}
	}
	return ret_list;
}

/***************************************************************************************************/
static bool isDiceAdjancent(Dice const& nextDice, vector<Dice> const& listAdjacentDies)
{
	for (vector<Dice>::const_iterator it = listAdjacentDies.begin(); it != listAdjacentDies.end(); ++it)
	{
		if ((nextDice.row == (*it).row) && (nextDice.column == (*it).column))
		{
			return true;
		}
	}
	return false;
}
