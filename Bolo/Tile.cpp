#include "Tile.h"
#include <random>

Tile::Tile()
{
}


Tile::~Tile()
{
}

void Tile::setTileInfo(int x, int y, bool walkable[], bool collidable[])
{
	offsetX_ = x;
	offsetY_ = y;
	for (int i = 0; i < 4; i++){
		subtileInfo_.walkable[i] = walkable[i];
		subtileInfo_.collidable[i] = collidable[i];
	}
}

void Tile::setRandomSubtiles()
{
	for (int i = 0; i < 3; i++){
		if (rand() % 10 < 1) {
			subtileInfo_.walkable[i] = false;
			subtileInfo_.collidable[i] = true;
		}
		else {
			subtileInfo_.walkable[i] = true;
			subtileInfo_.collidable[i] = false;
		}
	}
}

bool Tile::getSubtileWalkable(const int& i, const int& j) const
{
	return subtileInfo_.walkable[2 * i + j];
}

bool Tile::getSubtileCollide(const int& i, const int& j) const
{
	return subtileInfo_.collidable[2 * i + j];
}

int Tile::getX()
{
	return offsetX_;
}

int Tile::getY()
{
	return offsetY_;
}