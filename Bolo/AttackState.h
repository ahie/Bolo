#pragma once
#include "EntityState.h"

class AttackState : public EntityState
{
public:
	AttackState() {}
	virtual ~AttackState() {}
	virtual void enter(Entity& entity) = 0;
	virtual EntityState* update(Entity& entity, float dt) = 0;
	virtual EntityState* handleInput(Entity& entity, sf::Event inputEvent) = 0;
private:
	float swingTime_;
	float attackTime_;
};