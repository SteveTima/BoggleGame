#include "pch.h"
#include "../BoggleLIB/boggleConfig.h"
#include "../BoggleLIB/boggleRules.h"
#include "../BoggleLIB/boggleValidation.h"

//TEST(TestCaseName, TestName) {
//  EXPECT_EQ(1, 1);
//  EXPECT_TRUE(true);
//}

TEST(GameRules, checkCharLenght) {
	EXPECT_TRUE(checkCharLenght("TODO"));
	EXPECT_FALSE(checkCharLenght("TO"));
	EXPECT_TRUE(checkCharLenght("TOD"));
}


TEST(GameRules, score) {
	EXPECT_EQ(1, calculateScore("abc"));
	EXPECT_EQ(2, calculateScore("abcd"));
	EXPECT_EQ(3, calculateScore("abcde"));
	EXPECT_EQ(4, calculateScore("abcdef"));
	EXPECT_EQ(6, calculateScore("abcdefg"));
	EXPECT_EQ(12, calculateScore("abcdefgh"));
}

TEST(GameRules, toLowerCase) {
	std::string strVal = "ABCDEF";
	toLowerCase(strVal);
	EXPECT_EQ("abcdef", strVal);
	strVal = "AbCDe";
	toLowerCase(strVal);
	EXPECT_EQ("abcde", strVal);
	strVal = "Abc";
	toLowerCase(strVal);
	EXPECT_EQ("abc", strVal);
	strVal = "AbK";
	toLowerCase(strVal);
	EXPECT_EQ("abk", strVal);
}

TEST(GameRules, findWordInDict) {
	std::map<char, std::vector<std::string>> listOfWords;
	listOfWords['b'] = std::vector<std::string>();
	listOfWords['c'] = std::vector<std::string>();

	listOfWords['b'].push_back("belgium");
	listOfWords['b'].push_back("brazil");
	listOfWords['b'].push_back("botswana");

	listOfWords['c'].push_back("canada");
	listOfWords['c'].push_back("congo");
	listOfWords['c'].push_back("cameroun");

	EXPECT_TRUE(findWordInDict("brazil", listOfWords));
	EXPECT_TRUE(findWordInDict("cameroun", listOfWords));
	EXPECT_FALSE(findWordInDict("canad", listOfWords));
	EXPECT_FALSE(findWordInDict("canadas", listOfWords));
}

TEST(GameRules, tokenize) {
	std::vector<int> out_1 = tokenize("1 2 3 4", " ");
	std::vector<int> out_2 = tokenize("10-2022----104---", "-");
	EXPECT_TRUE(out_1.size() == 4);
	EXPECT_TRUE(out_2.size() == 3);
}

