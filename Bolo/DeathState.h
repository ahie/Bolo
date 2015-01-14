#pragma once
#include "Entity.h"
#include "EntityState.h"

class DeathState : public EntityState
{
public:
	DeathState() {}
	virtual ~DeathState() {}
	virtual void enter(Entity& entity) {
		entity.setAnimation(DEATH);
		entity.setColor(sf::Color::Red);
		timeToDeath_ = entity.getAnimLength();
	}
	virtual EntityState* update(Entity& entity, float dt) {
		timeToDeath_ -= dt;
		if (timeToDeath_ <= 0.05f)
			entity.kill();
		return nullptr;
	}
	virtual EntityState* handleInput(Entity& entity, EntityEvent event) {
		return nullptr;
	}
private:
	float timeToDeath_;
};
