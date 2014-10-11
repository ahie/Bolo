#pragma once
#include "Tile.h"
#include "NavGraph.h"

class Terrain
{
public:
	friend class NavGraph;
	Terrain(int width, int height) :
		width_(width), 
		height_(height), 
		tiles_(nullptr), 
		navGraph_(nullptr)
	{
		tiles_ = new Tile[width_*height_];
		for (int i = 0; i < width_; i++) {
			for (int j = 0; j < height_; j++) {
				(tiles_ + i*height_ + j)->setRandomSubtiles();
			}
		}
		navGraph_->generate(this);
	}
	~Terrain() 
	{
		delete[] tiles_;
		delete navGraph_;
	}
	bool walkable(sf::Vector2f coord)
	{
		int x = (int)(coord.x / TILE_WIDTH);
		int y = (int)(coord.y / TILE_HEIGHT);
		int subtileX;
		int subtileY;
		if (coord.x / TILE_WIDTH - x >= 0.5f) subtileX = 1;
		else subtileX = 0;
		if (coord.y / TILE_WIDTH - y >= 0.5f) subtileY = 1;
		else subtileY = 0;
		return (tiles_ + x*height_ + y)->getSubtileWalkable(subtileX, subtileY);
	}
private:
	int width_;
	int height_;
	Tile* tiles_;
	NavGraph* navGraph_;
	// has tileset
};