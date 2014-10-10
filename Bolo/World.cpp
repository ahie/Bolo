#include "World.h"


World::World()
{
	for (int i = 0; i < TERRAIN_HEIGHT; i++) {
		for (int j = 0; j < TERRAIN_WIDTH; j++) {
			terrain_[i][j].setRandomSubtiles();
		}
	}
	navGraph_.generate(this);
	hero_.setNavGraph(&navGraph_);
}


World::~World()
{
}

bool World::walkable(sf::Vector2f coord)
{
	int x = (int)(coord.x/TILE_WIDTH);
	int y = (int)(coord.y/TILE_HEIGHT);
	int subtileX;
	int subtileY;
	if (coord.x / TILE_WIDTH  - x >= 0.5f) subtileX = 1;
	else subtileX = 0;
	if (coord.y / TILE_WIDTH - y >= 0.5f) subtileY = 1;
	else subtileY = 0;
	return terrain_[x][y].getSubtileWalkable(subtileX,subtileY);
}

void World::handleInput(sf::Event inputEvent) 
{
	hero_.handleInput(inputEvent);
}

void World::update(sf::RenderWindow& window, float dt)
{
	hero_.update(dt);
	sf::View view;
	view.setCenter(hero_.getPos());
	view.setSize(200, 200);
	window.setView(view);
}

void World::render(sf::RenderWindow& window)
{
	// LOL
	sf::RectangleShape rect(sf::Vector2f(TILE_WIDTH / 2, TILE_HEIGHT / 2));
	rect.setFillColor(sf::Color(100,100,100));
	sf::RectangleShape rect2(sf::Vector2f(TILE_WIDTH / 2, TILE_HEIGHT / 2));
	rect2.setFillColor(sf::Color(255, 0, 0));
	for (int i = 0; i < TERRAIN_HEIGHT; i++) {
		for (int j = 0; j < TERRAIN_WIDTH; j++) {
			for (int k = 0; k < 2; k++) {
				for (int h = 0; h < 2; h++) {
					if (terrain_[i][j].getSubtileWalkable(k,h)) {
						rect.setPosition(sf::Vector2f(i*TILE_HEIGHT + k*TILE_HEIGHT / 2, j*TILE_WIDTH + h*TILE_WIDTH / 2));
						window.draw(rect);
					}
					else {
						rect2.setPosition(sf::Vector2f(i*TILE_HEIGHT + k*TILE_HEIGHT / 2, j*TILE_WIDTH + h*TILE_WIDTH / 2));
						window.draw(rect2);
					}
				}
			}
		}
	}
	hero_.render(window);
	navGraph_.render(window);
}