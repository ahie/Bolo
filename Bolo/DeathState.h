#pragma once
#include "Entity.h"
#include "EntityState.h"

class DeathState : public EntityState
{
public:
	DeathState() {}
	virtual ~DeathState() {}
	virtual void enter(Entity& entity) {
		entity.setColor(sf::Color::Red);
		timeToDeath_ = 1.0f;
	}
	virtual EntityState* update(Entity& entity, float dt) {
		timeToDeath_ -= dt;
		if (timeToDeath_ < 0.0f)
			entity.kill();
		return nullptr;
	}
	virtual EntityState* handleInput(Entity& entity, sf::Event inputEvent) {
		return nullptr;
	}
private:
	float timeToDeath_;
};