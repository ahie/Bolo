#include "MovingState.h"
#include "StandingState.h"
#include "AttackingState.h"
#include "Hero.h"
#include <SFML\Graphics\Color.hpp>


static sf::Vector2f normalize(const sf::Vector2f& source)
{
	float length = sqrt((source.x * source.x) + (source.y * source.y));
	if (length != 0)
		return sf::Vector2f(source.x / length, source.y / length);
	else
		return source;
}

MovingState::MovingState(Entity& entity, float x, float y) : 
	path_(entity.getPath(x, y)) {}


MovingState::~MovingState() {}

EntityState* MovingState::handleInput(Entity& entity, EntityEvent event)
{
	if (event.clicked) {
		if (event.clickType == EntityEvent::Click::RIGHT) {
			path_ = entity.getPath(event.clickPos.x,event.clickPos.y);
		}
		if (event.clickType == EntityEvent::Click::LEFT) {
			sf::Vector2f attackDirection = normalize(event.clickPos - entity.getPos());
			return new AttackingState(attackDirection);
		}
	}
	return nullptr;
}

EntityState* MovingState::update(Entity& entity, float dt)
{
	if (path_.empty())
		return new StandingState();
	entity.move(path_.back(), dt);
	if (dt > 0.0f) {
		path_.pop_back();
		return this->update(entity, dt);
	}
	return nullptr;
}

void MovingState::enter(Entity& entity)
{
	entity.setAnimation(WALK);
	entity.setColor(sf::Color(0, 0, 255));
}
