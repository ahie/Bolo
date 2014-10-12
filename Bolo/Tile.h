#pragma once

const int TILE_HEIGHT = 20;
const int TILE_WIDTH = 20;

class Tile
{
public:
	Tile();
	~Tile();
	void setRandomSubtiles();
	bool getSubtileWalkable(const int& i, const int& j) const;
	bool getSubtileCollide(const int& i, const int& j) const;
private:
	struct SubtileInfo {
		bool walkable[2][2];
		bool collidable[2][2];
	};
	SubtileInfo subtileInfo_;
	// tileset offset
};
