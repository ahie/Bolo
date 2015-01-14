#pragma once

const int TILE_HEIGHT = 64;
const int TILE_WIDTH = 64;

class Tile
{
public:
	Tile();
	~Tile();
	void setTileInfo(int x, int y, bool walkable[4], bool collidable[4]);
	void setRandomSubtiles();
	void setOffsets(int x, int y);
	bool getSubtileWalkable(const int& i, const int& j) const;
	bool getSubtileCollide(const int& i, const int& j) const;
	int getX();
	int getY();
private:
	struct SubtileInfo {
		bool walkable[4];
		bool collidable[4];
	};
	SubtileInfo subtileInfo_;
	// tileset offsets
	int offsetX_;
	int offsetY_;
};
