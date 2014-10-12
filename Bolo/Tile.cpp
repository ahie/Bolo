#include "Tile.h"
#include <random>


Tile::Tile()
{
}


Tile::~Tile()
{
}

void Tile::setRandomSubtiles()
{
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			if (rand() % 10 < 3) {
				subtileInfo_.walkable[i][j] = false;
				subtileInfo_.collidable[i][j] = false;
			}
			else {
				subtileInfo_.walkable[i][j] = true;
				subtileInfo_.collidable[i][j] = true;
			}
		}
	}
}

bool Tile::getSubtileWalkable(const int& i, const int& j) const
{
	return subtileInfo_.walkable[i][j];
}

bool Tile::getSubtileCollide(const int& i, const int& j) const
{
	return subtileInfo_.collidable[i][j];
}