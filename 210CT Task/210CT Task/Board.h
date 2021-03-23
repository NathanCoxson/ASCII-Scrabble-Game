#pragma once

#include "Common.h"
#include "Square.h"
#include "Bag.h"
#include "WordSet.h"

#include <string>


using std::string;

class Board
{
public:
	Square board_coordinates[15][15];
	bool starting_coordinates[15][15] = { {false} };
	WordSet words;
	Trie word_trie;

	Board();

	Board(WordSet w);

	~Board();

	///<summary>
	///Returns a word on the board given a starting position and direction.
	///</summary>
	string GetWord(Direction dir, int x, int y);

	///<summary>
	///Checks if the placement of a word/letter given a direction and position forms a legal placement.
	///</summary>
	ValidatedWord WordCheck(string word, Direction dir, DirectionType dir_type, int x, int y);

	///<summary>
	///Checks if the placement of a word/letter given a direction and position and set of tiles forms a legal placement.
	///</summary>
	ValidatedWord ValidWord(string word, Direction dir, int x, int y, vector<Tile>& tiles);

	///<summary>
	///Determines if a word can be applied to the board legally. If so, it will apply it to the board.
	///</summary>
	ValidatedWord ApplyWord(string word, Direction dir, int x, int y, vector<Tile>& tiles);

	///<summary>
	///Draws the board to the console.
	///</summary>
	void Draw();

};

