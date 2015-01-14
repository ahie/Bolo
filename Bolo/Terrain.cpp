#include "Terrain.h"

Terrain::Terrain(int width, int height, Tile* tiles, std::string tileset) :
width_(width),
height_(height),
tiles_(tiles),
navGraph_(nullptr)
{
	navGraph_ = new NavGraph;
	navGraph_->generate(this);

	sf::Image tilesetImage;
	tilesetImage.loadFromFile("Resources/Tilesets/" + tileset + ".png");
	tilesetImage.createMaskFromColor(sf::Color(255, 255, 255));
	tilesetTexture_.loadFromImage(tilesetImage);
	tilesetSprite_.setTexture(tilesetTexture_);
}

Terrain::~Terrain()
{
	delete[] tiles_;
	delete navGraph_;
}

bool Terrain::walkable(sf::Vector2f coord)
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

bool Terrain::checkCollision(sf::Vector2f at)
{
	if (at.x > width_*TILE_WIDTH || at.x < 0.0f ||
		at.y > height_*TILE_HEIGHT || at.y < 0.0f) return true;
	int x = (int)(at.x / TILE_WIDTH);
	int y = (int)(at.y / TILE_HEIGHT);
	int subtileX;
	int subtileY;
	if (at.x / TILE_WIDTH - x >= 0.5f) subtileX = 1;
	else subtileX = 0;
	if (at.y / TILE_WIDTH - y >= 0.5f) subtileY = 1;
	else subtileY = 0;
	return (tiles_ + x*height_ + y)->getSubtileCollide(subtileX, subtileY);
}

NavGraph* Terrain::getNavGraph()
{
	return navGraph_;
}

std::vector<RenderableSprite> Terrain::requestSprites()
{
	std::vector<RenderableSprite> sprites;
	for (int i = 0; i < width_; i++){
		for (int j = 0; j < height_; j++){
			int offsetX = (tiles_ + i*height_ + j)->getX();
			int offsetY = (tiles_ + i*height_ + j)->getY();
			tilesetSprite_.setTextureRect(sf::IntRect(
				sf::Vector2i(offsetX*(SPRITE_WIDTH + 1), offsetY*(SPRITE_HEIGHT + 1)),
				sf::Vector2i(SPRITE_WIDTH, SPRITE_HEIGHT)));
			sf::Vector2f pos = sf::Vector2f(i*TILE_WIDTH, j*TILE_HEIGHT);
			tilesetSprite_.setPosition(sf::Vector2f(pos.x - pos.y, (pos.x + pos.y) / 2.0f) - sf::Vector2f(64.0f, 128.0f));
			sprites.push_back(RenderableSprite(tilesetSprite_, pos));
		}
	}
	return sprites;
}

// old rendering function used for testing
void Terrain::render(sf::RenderWindow& window)
{
	for (int i = 0; i < width_; i++){
		for (int j = 0; j < height_; j++){
			int offsetX = (tiles_ + i*height_ + j)->getX();
			int offsetY = (tiles_ + i*height_ + j)->getY();
			tilesetSprite_.setTextureRect(sf::IntRect(
				sf::Vector2i(offsetX*(SPRITE_WIDTH + 1), offsetY*(SPRITE_HEIGHT + 1)),
				sf::Vector2i(SPRITE_WIDTH, SPRITE_HEIGHT)));
			tilesetSprite_.setPosition(
				sf::Vector2f(i*TILE_WIDTH - j*TILE_HEIGHT, (i*TILE_WIDTH + j*TILE_HEIGHT) / 2.0f)
				- sf::Vector2f(64.0f, 128.0f));
			window.draw(tilesetSprite_);
		}
	}
	navGraph_->render(window);
}