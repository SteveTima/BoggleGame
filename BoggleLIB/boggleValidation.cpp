#include "boggleValidation.h"

#include <ctype.h> /* isdigit()*/

#include "boggleRules.h"

using namespace std;


static string const USR_INPUT_DELIMITER = " ";
static InputString toPlayerString(std::string const& usrInput, std::map<int, Dice> const& boardMap);

/***************************************************************************************************/
bool findWordInDict(string const& word, map<char, vector<string>> const& listOfValidWords)
{
	bool match = false;
	char const firstChar = word.at(0);
	map<char, vector<string>>::const_iterator keyFound = listOfValidWords.find(firstChar);
	if (keyFound != listOfValidWords.end())
	{
		for (vector<string>::const_iterator it = (keyFound->second).begin(); it != (keyFound->second).end(); ++it)
		{
			if (word == (*it))
			{
				match = true;
				break;
			}
		}
	}
	return match;
}

/***************************************************************************************************/
int calculateScore(string const& value)
{
	int valueScore = 0;
	int len = (int) value.length();
	switch (len)
	{
	case 3:
		valueScore += 1;
		break;
	case 4:
		valueScore += 2;
		break;
	case 5:
		valueScore += 3;
		break;
	case 6:
		valueScore += 4;
		break;
	case 7:
		valueScore += 6;
		break;
	default:
		valueScore += 12;
		break;
	}
	return valueScore;
}

/***************************************************************************************************/
vector<InputString> stringToPlayerString(vector<string> const& playerInputs, map<int, Dice> const& boardMap)
{
	vector<InputString> castPlayerIn;
	int const playerInputsLen = (int) playerInputs.size();
	for (int i = 0; i < playerInputsLen; i++)
	{
		castPlayerIn.push_back(toPlayerString(playerInputs[i], boardMap));
	}
	return castPlayerIn;
}

/***************************************************************************************************/
vector<int> tokenize(string usrInput, string const& delimeter)
{
	vector<int> diesNbr{};
	string lastToken;
	int start = 0;
	int end = (int) usrInput.find(delimeter);
	while (end != -1) {
		if ((end - start) > 0)
		{
			diesNbr.push_back(stoi(usrInput.substr(start, end - start)));
		}
		start = end + (int)delimeter.size();
		end = (int)usrInput.find(delimeter, start);
	}

	lastToken = usrInput.substr(start, end - start);
	if (!(lastToken.empty()))
	{
		diesNbr.push_back(stoi(lastToken));
	}

	return diesNbr;
}

/***************************************************************************************************/
vector<InputString> validate(vector<InputString> const& words)
{
	vector<InputString> validWords;
	int const wordsLenght = (int) words.size();
	for (int i = 0; i < wordsLenght; i++)
	{
		if (isWordValid(words[i]))
		{
			validWords.push_back(words[i]);
		}
	}
	return validWords;
}

/***************************************************************************************************/
bool isWordValid(InputString const& word)
{
	bool sizeValid = checkCharLenght(word.strValue);
	bool redundancyValid = !(checkRedundancy(word.dies));
	bool positionValid = checkCharPositions(word.dies);
	if (sizeValid && redundancyValid && positionValid)
	{
		return true;
	}
	return false;
}

/***************************************************************************************************/
int getScore(vector<InputString>& words, map<char, vector<string>> const& wordsDictionary)
{
	int playerScore = 0;
	int const inputLenght = (int) words.size();
	for (int i = 0; i < inputLenght; i++)
	{
		InputString singleWord = words[i];
		if (findWordInDict(singleWord.strValue, wordsDictionary))
		{
			words[i].score = calculateScore(singleWord.strValue);
			playerScore += words[i].score;
		}
	}
	return playerScore;
}

/***************************************************************************************************/
bool isUserInputValid(string const usrInput)
{
	char const spaceCharacter = ' ';
	int const usrInputLen = (int) usrInput.length();
	for (int i = 0; i < usrInputLen; i++)
	{
		char ch = usrInput[i];
		if (!(isdigit(ch) || (ch == spaceCharacter)))
		{
			return false;
		}
	}
	return true;
}

/***************************************************************************************************/
string makeStringFromDies(vector<Dice> const& listOfDies)
{
	string strValue = "";
	for (vector<Dice>::const_iterator it = listOfDies.begin(); it != listOfDies.end(); ++it)
	{
		strValue += (*it).value;
	}
	return strValue;
}

// STATIC FUNCTIONS

/***************************************************************************************************/
static InputString toPlayerString(string const& usrInput, map<int, Dice> const& boardMap)
{
	InputString newPlayerValue;
	vector<int> diesNumber = tokenize(usrInput, USR_INPUT_DELIMITER);
	int const diesNumberLenght = (int) diesNumber.size();
	for (int i = 0; i < diesNumberLenght; i++)
	{
		int key = diesNumber[i];
		map<int, Dice>::const_iterator keyFound = boardMap.find(key);
		if (keyFound != boardMap.end())
		{
			newPlayerValue.strValue.push_back(keyFound->second.value);
			newPlayerValue.dies.push_back(keyFound->second);
		}
	}
	return newPlayerValue;
}

