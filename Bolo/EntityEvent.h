#pragma once
#include <SFML\System\Vector2.hpp>

struct EntityEvent
{
	enum Click { RIGHT, LEFT };
	EntityEvent(bool clicked, Click type, sf::Vector2f pos) :
		clicked(clicked), clickType(type), clickPos(pos) {}
	Click clickType;
	bool clicked;
	sf::Vector2f clickPos;
};