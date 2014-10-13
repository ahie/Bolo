#pragma once
#include "EntityState.h"
#include "Entity.h"
#include "StandingState.h"
#include <SFML\Graphics\Color.hpp>

class AttackingState : public EntityState
{
public:
	AttackingState(sf::Vector2f direction): 
		swingTime_(1.2), 
		attackTime_(1.5), 
		attacked_(false), 
		direction_(direction) {}
	virtual ~AttackingState() {}
	virtual void enter(Entity& entity)
	{
		entity.setColor(sf::Color(100,100,0));
	}
	virtual EntityState* update(Entity& entity, float dt)
	{
		swingTime_ -= dt;
		attackTime_ -= dt;
		if (swingTime_ < 0.f && !attacked_) {
			entity.attack(direction_);
			attacked_ = true;
		}
		if (attackTime_ < 0.f) return new StandingState();
		return nullptr;
	}
	virtual EntityState* handleInput(Entity& entity, sf::Event inputEvent) { return nullptr; }
private:
	sf::Vector2f direction_;
	float swingTime_;
	float attackTime_;
	bool attacked_;
};