#pragma once

#include "boggleTypDef.h"


/**
 * @brief Check if the lenght of a string exceeds the allowed minimal lenght.
 *
 * @param word string value whose lenght will be analyzed
 * @return True if the lenght of the string exceeds the minimal lenght,
 *         otherwise False.
 */
bool checkCharLenght(std::string const& word);

/**
 * @brief Check if a dice is present in a vector more than once.
 *
 * @param listOfDice vector of dies
 * @return True if a value is present more than once, otherwise False.
 */
bool checkRedundancy(std::vector<Dice> const& listOfDice);

/**
 * @brief Check if all dies in a vector are sequentially adjacent.
 * 
 * Those horizontally, vertically, and diagonally neighbouring the current one.
 *
 * @param listOfDice vector of dies
 * @return True if all dies are sequentially adjacent, otherwise False.
 */
bool checkCharPositions(std::vector<Dice> const& listOfDice);


