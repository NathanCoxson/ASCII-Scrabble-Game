#pragma once

#include "Player.h"

class HumanPlayer : public Player
{
public:

	HumanPlayer(int a, PlayerType b) : Player(a, b) {}

	virtual int Turn(Board& board, vector<Player*>& players) override;

};

