#include "Player.h"

#include <iostream>

using std::cout;
using std::endl;

Player::Player(int player_id, PlayerType player_type)
{
	id = player_id;
	type = player_type;
}

void Player::Replenish(Bag& bag)
{
	while (tiles.size() < 7)
	{
		if (bag.tiles.size() == 0) { return; }
		tiles.push_back(bag.GrabTile());
	}
}

void Player::CurrentTiles()
{
	cout << "-------";
	for (auto tile : tiles)
	{
		cout << "--|" << tile.letter << "|--";
	}
	cout << "-------" << endl;
}

void Player::NewTiles(Bag& bag)
{
	for (auto tile : tiles)
	{
		bag.tiles += tile.letter;
	}
	tiles.clear();
	Replenish(bag);
}

int Player::Turn(Board& board, vector<Player*>& players)
{
	return 0;
}