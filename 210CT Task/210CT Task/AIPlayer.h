#pragma once

#include "Player.h"

class AIPlayer : public Player
{
public:
	
	AIPlayer(int a, PlayerType b) : Player(a, b) {}

	virtual int Turn(Board& board, vector<Player*>& players) override;

	///<summary>
	///Parses through a vector of strings and returns the word determined to be the best play.
	///</summary>
	BasicWord ParseWords(vector<string> words, string pre);

	///<summary>
	///Returns a vector of possible plays that the AI can perform on the board.
	///</summary>
	vector<AIPlay> FindPlays(Board& board);

	///<summary>
	///Returns a vector of possible plays that the AI can perform on the board with Left to Right words.
	///</summary>
	vector<AIPlay> FindPlaysLtR(Board& board);

	///<summary>
	///Returns a vector of possible plays that the AI can perform on the board with Top to Bottom words.
	///</summary>
	vector<AIPlay> FindPlaysTtB(Board& board);

};

