#pragma once


#include "boggleTypDef.h"

#include <map>

#define WORD_LENGHT_MIN 3


/**
 * Create a new container with keys corresponding to each
 * letter of the alphabet.
 *
 * Each key has an empty value.
 *
 * @param 
 * @return container with keys and empty values.
 */
std::map<char, std::vector<std::string>> createEmptyDictionary(void);

/**
 * @brief Set new values for each key in a container.
 *
 * @param pathFileName  Full path of the file wich contains all values.
 * @param wordsDictionary Container whose each key will get new values.
 * @return True if file exists , otherwise False.
 */
bool fillDictionary(std::string pathFileName, std::map<char, std::vector<std::string>>& wordsDictionary);



/**
 * @brief Get the full path of the file wich contains all string values.
 *
 * @param 
 * @return full path of the file.
 */
std::string getWordsDictDatafilePath(void);

// Show text and data on Board
/**
 * @brief Generate dies values to display for the game.
 *
 * @param 
 * @return vector of values
 */
std::vector<Dice> generateListOfDiesValues(void); // only for gui-project

/**
 * @brief Create a container of values to display for the game.
 *
 * @param
 * @return container of values
 */
std::map<int, Dice> createMapOfDiesValues(void); // only for console-project

// Only for unit test
void toLowerCase(std::string& value);
