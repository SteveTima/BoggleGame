#include "boggleConfig.h"

#include <assert.h>
#include <fstream>
#include <random>
#include <direct.h>

using namespace std;


static string const WORDS_DICT_FILENAME = "wordlist.txt";

/***************************************************************************************************/
map<char, vector<string>> createEmptyDictionary(void)
{
	map<char, vector<string>> dict;
	char const firstChar = 'a';
	char const lastChar = 'z';
	for (char ch = firstChar; ch <= lastChar; ch++)
	{
		dict[ch] = vector<string>();
	}
	return dict;
}

/***************************************************************************************************/
bool fillDictionary(string pathFileName, map<char, vector<string>>& listOfValidWords)
{
	ifstream wordFile(pathFileName);

	if (wordFile)
	{
		string word;
		while (getline(wordFile, word))
		{
			toLowerCase(word);
			map<char, vector<string>>::iterator keyFound = listOfValidWords.find(word.at(0));
			if (keyFound != listOfValidWords.end())
			{
				(keyFound->second).push_back(word);
			}
			else
			{
				// TODO: Warning: The string value 'word' will not be saved in the game dictonary.
			}
		}
		return true;
	}
	else
	{
		// TODO: ERROR: Failed to open file
		return false;
	}
}

/***************************************************************************************************/
void toLowerCase(std::string& value)
{
	//TODO: ERROR: What if the value contains invalid characters such as '?', '%', '&' etc...
	int const strLen = (int) value.length();
	for (int i = 0; i < strLen; i++)
	{
		if (isupper(value[i]))
		{
			value[i] = tolower(value[i]);
		}
	}
}

/***************************************************************************************************/
vector<Dice> generateListOfDiesValues(void)
{
	vector<Dice> listOfDiesVal;
	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_int_distribution<int> distr(0, (NBR_OF_SIDES_PER_DICE - 1));
	int i = 0;
	for (int row = 0; row < NBR_OF_ROWS; row++)
	{
		for (int col = 0; col < NBR_OF_COLUMNS; col++)
		{
			int diceIndex = distr(eng);
			char diceCharVal = DIE_MATRIX[i++][diceIndex];
			listOfDiesVal.push_back(Dice(row, col, tolower(diceCharVal)));
			
		}
	}
	assert(listOfDiesVal.size() == (NBR_OF_ROWS * NBR_OF_COLUMNS));
	return listOfDiesVal;
}

/***************************************************************************************************/
map<int, Dice> createMapOfDiesValues(void)
{
	map<int, Dice> mapOfDies;
	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_int_distribution<int> distr(0, (NBR_OF_SIDES_PER_DICE - 1));
	int i = 0;
	int j = 0;
	for (int row = 0; row < NBR_OF_ROWS; row++)
	{
		for (int col = 0; col < NBR_OF_COLUMNS; col++)
		{
			int diceIndex = distr(eng);
			char diceCharVal = DIE_MATRIX[i++][diceIndex];
			mapOfDies[++j] = Dice(row, col, diceCharVal);
		}
	}
	assert(mapOfDies.size() == (NBR_OF_ROWS * NBR_OF_COLUMNS));
	return mapOfDies;
}

/***************************************************************************************************/
string getWordsDictDatafilePath(void)
{
	string fullPath;
	char tmp[256];
	_getcwd(tmp, 256);
	fullPath = tmp;
	fullPath.append("\\");
	fullPath.append(WORDS_DICT_FILENAME);
	return fullPath;
}