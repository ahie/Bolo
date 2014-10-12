#pragma once
#include "EntityState.h"

class StandingState :
	public EntityState
{
public:
	StandingState();
	~StandingState();
	virtual void enter(Entity& hero);
	virtual EntityState* update(Entity& hero, float dt);
	virtual EntityState* handleInput(Entity& hero, sf::Event inputEvent);
};

