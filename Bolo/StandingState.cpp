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

void StandingState::enter(Hero& hero)
{
	hero.setColor(sf::Color(0, 255, 0));
}

HeroState* StandingState::handleInput(Hero& hero, sf::Event inputEvent)
{
	if (inputEvent.type == sf::Event::MouseButtonPressed) {
		if (inputEvent.mouseButton.button == sf::Mouse::Left) {
			return new MovingState();
		}
	}
	return nullptr;
}

void StandingState::enter(Hero& hero, sf::Event inputEvent)
{
	this->enter(hero);
}

HeroState* StandingState::update(Hero& hero, float dt) 
{
	return nullptr;
}