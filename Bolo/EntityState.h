#pragma once
#include <SFML\Window\Event.hpp>

class Entity;

class EntityState
{
public:
	EntityState() {}
	virtual ~EntityState() {}
	virtual void enter(Entity& entity) = 0;
	virtual void enter(Entity& entity, sf::Event inputEvent) = 0;
	virtual EntityState* update(Entity& hero, float dt) = 0;
	virtual EntityState* handleInput(Entity& hero, sf::Event inputEvent) = 0;
};

