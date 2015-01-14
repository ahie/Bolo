#include "StandingState.h"
#include "MovingState.h"
#include "AttackingState.h"
#include "Entity.h"
#include <SFML/Graphics/Color.hpp>


static sf::Vector2f normalize(const sf::Vector2f& source)
{
	float length = sqrt((source.x * source.x) + (source.y * source.y));
	if (length != 0)
		return sf::Vector2f(source.x / length, source.y / length);
	else
		return source;
}

StandingState::StandingState()
{
}


StandingState::~StandingState()
{
}

void StandingState::enter(Entity& entity)
{
	entity.setAnimation(STAND);
	entity.setColor(sf::Color(0, 255, 0));
}

EntityState* StandingState::handleInput(Entity& entity, EntityEvent event)
{
	if (event.clicked) {
		if (event.clickType == EntityEvent::Click::RIGHT) {
			return new MovingState(entity, event.clickPos.x, event.clickPos.y);
		}
		if (event.clickType == EntityEvent::Click::LEFT) {
			sf::Vector2f attackDirection = normalize(event.clickPos - entity.getPos());
			return new AttackingState(attackDirection);
		}
	}
	return nullptr;
}

EntityState* StandingState::update(Entity& entity, float dt) 
{
	return nullptr;
}
