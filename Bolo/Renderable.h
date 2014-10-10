#pragma once
#include <SFML/Graphics.hpp>

class Renderable
{
public:
	Renderable() {};
	virtual ~Renderable() {};
	virtual void render(sf::RenderWindow& window) = 0;
};

