#pragma once

#include "common.h"

#include <string>
#include <random>

using std::string;

class Bag
{
public:
	string tiles = "aaaaaaaaabbccddddeeeeeeeeeeeeffggghhiiiiiiiiijkllllmmnnnnnnooooooooppqrrrrrrssssttttttuuuuvvwwxyyz##";

	///<summary>
	///Returns a randomly selected tile from the bag.
	///</summary>
	Tile GrabTile();

};

