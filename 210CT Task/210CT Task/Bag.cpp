#include "Bag.h"

Tile Bag::GrabTile()
{
	if (tiles.size() > 0)
	{
		std::random_device generator;
		std::uniform_int_distribution<int> distribution(0, tiles.length() - 1);

		int random_integer = distribution(generator);
		
		Tile tile(tiles[random_integer], ((tiles[random_integer] == '#') ? true : false));

		tiles.erase(random_integer, 1);
		return tile;
	}
	return Tile();
}