#pragma once
#include "EntityState.h"
#include <vector>

class MovingState :
	public EntityState
{
public:
	MovingState();
	~MovingState();
	virtual void enter(Entity& hero);
	virtual void enter(Entity& hero, sf::Event inputEvent);
	virtual EntityState* update(Entity& hero, float dt);
	virtual EntityState* handleInput(Entity& hero, sf::Event inputEvent);
private:
	std::vector<sf::Vector2f> path_;
};
