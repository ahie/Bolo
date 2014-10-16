#pragma once
#include "EntityState.h"
#include <vector>

class MovingState :
	public EntityState
{
public:
	MovingState(Entity& entity, float x, float y);
	~MovingState();
	virtual void enter(Entity& entity);
	virtual EntityState* update(Entity& entity, float dt);
	virtual EntityState* handleInput(Entity& entity, EntityEvent event);
private:
	std::vector<sf::Vector2f> path_;
};
