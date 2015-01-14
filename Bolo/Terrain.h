#pragma once
#include "Tile.h"
#include "NavGraph.h"
#include "Renderable.h"

#include <string>

const int SPRITE_WIDTH = 128;
const int SPRITE_HEIGHT = 192;

class Terrain: public Renderable
{
public:
	friend class NavGraph;
	Terrain(int width, int height, Tile* tiles, std::string tileset);
	~Terrain();
	bool walkable(sf::Vector2f coord);
	bool checkCollision(sf::Vector2f at);
	NavGraph* getNavGraph();
	void render(sf::RenderWindow& window);
	std::vector<RenderableSprite> requestSprites();
private:
	int width_;
	int height_;
	Tile* tiles_;
	NavGraph* navGraph_;

	// has tileset
	sf::Texture tilesetTexture_; // load from image
	sf::Sprite tilesetSprite_; // set from texture
	std::vector<RenderableSprite> sprites_;
};