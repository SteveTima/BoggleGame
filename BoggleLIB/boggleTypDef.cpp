#include "boggleTypDef.h"

using namespace std;

/***************************************************************************************************/
Dice::Dice()
{
	row = 0;
	column = 0;
	value = '\0';
}
Dice::Dice(int r, int c)
{
	row = r;
	column = c;
	value = '\0';
}
Dice::Dice(char v)
{
	row = 0;
	column = 0;
	value = v;
}
Dice::Dice(int r, int c, char v)
{
	row = r;
	column = c;
	value = v;
}


/***************************************************************************************************/
InputString::InputString()
{
	strValue = "";
	score = 0;
	dies = vector<Dice>();
}
InputString::InputString(string p_strValue)
{
	strValue = p_strValue;
	score = 0;
	dies = vector<Dice>();
}
InputString::InputString(vector<Dice> p_dies, string p_strValue)
{
	strValue = p_strValue;
	dies = p_dies;
	score = 0;
}


/***************************************************************************************************/
Player::Player(string p_name)
{
	name = p_name;
	score = 0;
	playerWords = vector<InputString>();
}
Player::Player()
{
	name = "";
	score = 0;
	playerWords = vector<InputString>();
}