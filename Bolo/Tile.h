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
private:
	struct SubtileInfo {
		bool walkable[2][2];
	};
	SubtileInfo subtileInfo_;
};
