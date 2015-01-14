#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

struct RenderableSprite {
	RenderableSprite() : sprite(sf::Sprite()), pos(sf::Vector2f()) {}
	RenderableSprite(sf::Sprite s, sf::Vector2f p) : sprite(s), pos(p) {}
	sf::Sprite sprite;
	sf::Vector2f pos; // for depth sorting
	inline bool operator<(const RenderableSprite& rhs) const 
	{ 
		return (this->pos.x + this->pos.y) < (rhs.pos.x + rhs.pos.y);
	}
};

class Renderable
{
public:
	Renderable() {}
	virtual ~Renderable() {}
	virtual void render(sf::RenderWindow& window) = 0;
	virtual RenderableSprite requestSprite() { return RenderableSprite(); }
	virtual std::vector<RenderableSprite> requestSprites() { return std::vector<RenderableSprite>(); }
};
