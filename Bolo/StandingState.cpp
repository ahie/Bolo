#include "StandingState.h"
#include "MovingState.h"
#include "AttackingState.h"
#include "entity.h"
#include <SFML\Graphics\Color.hpp>


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
	entity.setColor(sf::Color(0, 255, 0));
}

EntityState* StandingState::handleInput(Entity& entity, sf::Event inputEvent)
{
	if (inputEvent.type == sf::Event::MouseButtonPressed) {
		if (inputEvent.mouseButton.button == sf::Mouse::Right) {
			return new MovingState(entity,inputEvent.mouseButton.x,inputEvent.mouseButton.y);
		}
		if (inputEvent.mouseButton.button == sf::Mouse::Left) {
			sf::Vector2f attackDirection = normalize(sf::Vector2f(inputEvent.mouseButton.x, inputEvent.mouseButton.x) - entity.getPos());
			return new AttackingState(attackDirection);
		}
	}
	return nullptr;
}

EntityState* StandingState::update(Entity& entity, float dt) 
{
	return nullptr;
}