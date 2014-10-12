#include "StandingState.h"
#include "MovingState.h"
#include "AttackingState.h"
#include "entity.h"
#include <SFML\Graphics\Color.hpp>


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
		if (inputEvent.mouseButton.button == sf::Mouse::Left) {
			return new MovingState(entity,inputEvent.mouseButton.x,inputEvent.mouseButton.y);
		}
		if (inputEvent.mouseButton.button == sf::Mouse::Left) {
			return new AttackingState();
		}
	}
	return nullptr;
}

EntityState* StandingState::update(Entity& entity, float dt) 
{
	return nullptr;
}