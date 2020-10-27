#pragma once

#include "Common.h"
#include "Bag.h"
#include "Square.h"
#include "Board.h"
#include "WordSet.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"

#include <string>

using std::string;

///<summary>
///This brings multiple classes together to create a game of scrabble
///</summary>
class Scrabble
{
public:

	Board* board;
	Bag bag;
	vector<Player*> players;

	Scrabble(string path);

	~Scrabble();

	///<summary>
	///This function will setup the basic parts of the scrabble game
	///</summary>
	void Setup();

	///<summary>
	///This function will perform the main game step
	///</summary>
	void Step();

	///<summary>
	///This function will return true if the win conditions are met
	///</summary>
	bool Won();

	///<summary>
	///This function will end the scrabble game and display final results
	///</summary>
	void End();

};

