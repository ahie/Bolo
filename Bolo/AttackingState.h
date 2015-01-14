#pragma once
#include "EntityState.h"
#include "Entity.h"
#include "StandingState.h"
#include <SFML/Graphics/Color.hpp>

class AttackingState : public EntityState
{
public:
	AttackingState(sf::Vector2f direction): 
		swingTime_(0.0f), 
		attackTime_(0.0f), 
		attacked_(false), 
		direction_(direction) {}
	virtual ~AttackingState() {}
	virtual void enter(Entity& entity)
	{
		attackTime_ = entity.getAttackSpeed();
		entity.updateOrientation(direction_);
		entity.setAnimation(ATTACK);
		entity.setColor(sf::Color(100,100,0));
	}
	virtual EntityState* update(Entity& entity, float dt)
	{
		swingTime_ += dt;
		if (swingTime_ >= 0.8*attackTime_ && !attacked_) {
			entity.attack(direction_);
			attacked_ = true;
		}
		if (swingTime_ >= attackTime_) return new StandingState();
		return nullptr;
	}
	virtual EntityState* handleInput(Entity& entity, EntityEvent event) { return nullptr; }
private:
	sf::Vector2f direction_;
	float swingTime_;
	float attackTime_;
	bool attacked_;
};