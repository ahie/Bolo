#include "StandingState.h"
#include "MovingState.h"
#include "Hero.h"
#include <SFML\Graphics\Color.hpp>


StandingState::StandingState()
{
}


StandingState::~StandingState()
{
}

void StandingState::enter(Entity& hero)
{
	hero.setColor(sf::Color(0, 255, 0));
}

EntityState* StandingState::handleInput(Entity& hero, sf::Event inputEvent)
{
	if (inputEvent.type == sf::Event::MouseButtonPressed) {
		if (inputEvent.mouseButton.button == sf::Mouse::Left) {
			return new MovingState();
		}
	}
	return nullptr;
}

void StandingState::enter(Entity& hero, sf::Event inputEvent)
{
	this->enter(hero);
}

EntityState* StandingState::update(Entity& hero, float dt) 
{
	return nullptr;
}