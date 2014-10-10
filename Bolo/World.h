#pragma once
#include "Hero.h"
#include "Tile.h"
#include "NavGraph.h"
#include "Renderable.h"

const int TERRAIN_HEIGHT = 100;
const int TERRAIN_WIDTH = 100;

class World : public Renderable
{
public:
	World();
	~World();
	bool walkable(sf::Vector2f coord);
	void render(sf::RenderWindow& window);
	void handleInput(sf::Event inputEvent);
	void update(sf::RenderWindow& window, float dt);
	Hero* getHero() { return &hero_; }
private:
	Hero hero_;
	Tile terrain_[TERRAIN_HEIGHT][TERRAIN_WIDTH];
	NavGraph navGraph_;
};

