#pragma once

#include "boggleTypDef.h"

#include <map>

/**
 * @brief Check the validity of a data entered by the player.
 * 
 * Only Digits and spaces are permitted
 *
 * @param usrInput string value entered by the player
 * @return True if the string contains only digits and spaces, otherwise False.
 */
bool isUserInputValid(std::string const usrInput);

/**
 * @brief Convert each string to a customized datatyp.
 *
 * @param playerInputs List of string values to be converted
 * @param boardMap Container that contains the matches of each string value to be converted
 * @return List of matching values.
 */
std::vector<InputString> stringToPlayerString(std::vector<std::string> const& playerInputs, std::map<int, Dice> const& boardMap);

/**
 * @brief Filter valid values and return them.
 *
 * @param words List of string values to be filtered
 * @return List of valid values.
 */
std::vector<InputString> validate(std::vector<InputString> const& words);

/**
 * @brief Sum the score of each word of a player founded in a List of game valid words.
 *
 * @param words List of words of the player
 * @param wordsDictionary List of game valid words
 * @return Sum of each score of a valid word.
 */
int getScore(std::vector<InputString>& words, std::map<char, std::vector<std::string>> const& wordsDictionary);

/**
 * @brief Make a string from a list of dice.
 *
 * @param listOfDies List of dice
 * @return String value.
 */
std::string makeStringFromDies(std::vector<Dice> const& listOfDies);

/**
 * @brief Check the validity of a string.
 *
 * @param word string value to be checked
 * @return True if the string value is valid, otherwise False.
 */
bool isWordValid(InputString const& word);

// Only for unit test
std::vector<int> tokenize(std::string usrInput, std::string const& delimeter);
bool findWordInDict(std::string const& word, std::map<char, std::vector<std::string>> const& wordsDictionary); 
int calculateScore(std::string const& value);