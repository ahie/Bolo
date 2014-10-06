#pragma once
#include <SFML/Graphics.hpp>

const int TILE_TEXTURE_HEIGHT = 192;
const int TILE_TEXTURE_WIDTH = 128;
const int TILE_HEIGHT = 64;
const int TILE_WIDTH = TILE_TEXTURE_WIDTH / 2;

class Tile
{
public:
	Tile(float x, float y, sf::Texture* texture, int offsetX, int offsetY);
	~Tile();
	virtual void render(sf::RenderWindow& window);

private:
	sf::Texture* texture;
	sf::Sprite sprite;
	float x;
	float y;

	struct SubtileInfo {
		bool walkable;
	};
	SubtileInfo subtile[4];
};
