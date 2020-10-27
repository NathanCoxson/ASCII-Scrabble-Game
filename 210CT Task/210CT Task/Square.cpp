#include "Square.h"

Square::Square() { square_type = 0; tile.letter = '_'; tile.blank = true; }
Square::Square(int type) { square_type = type; tile.letter = '_'; tile.blank = true; }
Square::Square(char currentLetter) { tile.letter = currentLetter; square_type = 0; tile.blank = false; }
Square::Square(char currentLetter, int type) { tile.letter = currentLetter; square_type = type; tile.blank = false; }

int Square::Value()
{
	switch (square_type)
	{
	case SquareType::eNormal: return LetterPointCalculator(tile.letter);
	case SquareType::eDoubleLetter: return LetterPointCalculator(tile.letter) * 2;
	case SquareType::eTripleLetter: return LetterPointCalculator(tile.letter) * 3;
	case SquareType::eDoubleWord: return LetterPointCalculator(tile.letter);
	case SquareType::eTripleWord: return LetterPointCalculator(tile.letter);
	}
}

int Square::NormalValue() { return LetterPointCalculator(tile.letter); }

int Square::WordMultiplier()
{
	switch (square_type)
	{
	case SquareType::eNormal: return 1;
	case SquareType::eDoubleLetter: return 1;
	case SquareType::eTripleLetter: return 1;
	case SquareType::eDoubleWord: return 2;
	case SquareType::eTripleWord: return 3;
	}
}

int Square::LetterMultiplier()
{
	switch (square_type)
	{
	case SquareType::eNormal: return 1;
	case SquareType::eDoubleLetter: return 2;
	case SquareType::eTripleLetter: return 3;
	case SquareType::eDoubleWord: return 1;
	case SquareType::eTripleWord: return 1;
	}
}

string Square::ReturnLetter()
{
	switch (square_type)
	{
	case SquareType::eNormal: return reset + char(toupper(tile.letter));
	case SquareType::eDoubleLetter: return bright_cyan + char(toupper(tile.letter)) + reset;
	case SquareType::eTripleLetter: return blue + char(toupper(tile.letter)) + reset;
	case SquareType::eDoubleWord: return bright_magenta + char(toupper(tile.letter)) + reset;
	case SquareType::eTripleWord: return red + char(toupper(tile.letter)) + reset;
	}
}
