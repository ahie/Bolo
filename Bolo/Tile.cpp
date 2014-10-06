#include "Tile.h"

Tile::Tile(float x, float y,
	sf::Texture* texture,
	int offsetX, int offsetY) :
	x(x), y(y), texture(texture)
{
	this->sprite.setTexture(*texture);
	this->sprite.setTextureRect(
		sf::IntRect(TILE_TEXTURE_WIDTH * offsetX + offsetX,
		TILE_TEXTURE_HEIGHT * offsetY + offsetY,
		TILE_TEXTURE_WIDTH, TILE_TEXTURE_HEIGHT));
}


Tile::~Tile()
{
}

void Tile::render(sf::RenderWindow& window)
{
	this->sprite.setPosition(x - y, (this->x + this->y) / 2);
	window.draw(this->sprite);
}