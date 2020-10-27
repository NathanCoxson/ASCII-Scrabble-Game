#pragma once
#include <string>
#include "Common.h"

using std::string;

///<summary>
///This class represents a square on the scrabble board
///</summary>
class Square
{
public:
	int square_type;
	Tile tile;
	string reset = "\033[0m";
	string bright_green = "\033[1;92m";
	string green = "\033[92m";
	string bright_yellow = "\033[1;93m";
	string yellow = "\033[93m";
	string bright_cyan = "\033[1;96m";
	string cyan = "\033[96m";
	string bright_blue = "\033[1;94m";
	string blue = "\033[94m";
	string bright_red = "\033[91m";
	string red = "\033[1;91m";
	string bright_magenta = "\033[1;95m";
	string magenta = "\033[95m";

	enum SquareType
	{
		eNormal,
		eDoubleLetter,
		eTripleLetter,
		eDoubleWord,
		eTripleWord
	};

	Square();
	Square(int type);
	Square(char currentLetter);
	Square(char currentLetter, int type);

	///<summary>
	///This function will return the value of the current boardsquare
	///</summary>
	int Value();

	///<summary>
	///This function will return the value of the square's letter without letter multiplication
	///</summary>
	int NormalValue();

	///<summary>
	///This function will return the value of the square's word multiplier
	///</summary>
	int WordMultiplier();

	///<summary>
	///This function will return the value of the square's letter multiplier
	///</summary>
	int LetterMultiplier();

	///<summary>
	///This function will return the letter with colour formatting for console
	///</summary>
	string ReturnLetter();
};

