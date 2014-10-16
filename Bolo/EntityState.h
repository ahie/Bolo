#pragma once
#include "EntityEvent.h"

class Entity;

class EntityState
{
public:
	EntityState() {}
	virtual ~EntityState() {}
	virtual void enter(Entity& entity) = 0;
	virtual EntityState* update(Entity& entity, float dt) = 0;
	virtual EntityState* handleInput(Entity& entity, EntityEvent event) = 0;
};

