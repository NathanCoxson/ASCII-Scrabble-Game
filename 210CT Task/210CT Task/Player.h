#pragma once

#include "Common.h"
#include "Bag.h"
#include "Board.h"

///<summary>
///This class is a base class to represent a player, not to be used on its own
///</summary>
class Player
{
public:

	vector<Tile> tiles;
	int id;
	int points = 0;
	PlayerType type;
	PlayerAction last_action = PlayerAction::eNoAction;
	string last_played_word = "";

	///<summary>
	///Constructor for Player Class. 
	///</summary>
	Player(int player_id, PlayerType player_type);

	///<summary>
	///Replenishes the player's hand up to 7 tiles.
	///</summary>
	virtual void Replenish(Bag& bag);

	///<summary>
	///Outputs the player's hand to console.
	///</summary>
	virtual void CurrentTiles();

	///<summary>
	///Performs the player's turn. Returns the amount of points the player has gained.
	///</summary>
	virtual int Turn(Board& board, vector<Player*>& players);

	///<summary>
	///Gives the player an entirely fresh hand.
	///</summary>
	virtual void NewTiles(Bag& bag);
};

