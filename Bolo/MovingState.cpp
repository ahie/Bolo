#include "MovingState.h"
#include "StandingState.h"
#include "Hero.h"
#include <SFML\Graphics\Color.hpp>


MovingState::MovingState()
{
}


MovingState::~MovingState()
{
}

HeroState* MovingState::handleInput(Hero& hero, sf::Event inputEvent)
{
	if (inputEvent.type == sf::Event::MouseButtonPressed) {
		if (inputEvent.mouseButton.button == sf::Mouse::Left) {
			path_ = hero.getPath(inputEvent.mouseButton.x,
									inputEvent.mouseButton.y);
		}
	}
	return nullptr;
}

HeroState* MovingState::update(Hero& hero, float dt)
{
	if (path_.empty())
		return new StandingState();
	hero.move(path_.back(), dt);
	if (dt > 0.0f) {
		path_.pop_back();
		return this->update(hero, dt);
	}
	return nullptr;
}

void MovingState::enter(Hero& hero)
{
	hero.setColor(sf::Color(0, 0, 255));
}

void MovingState::enter(Hero& hero, sf::Event inputEvent)
{
	this->enter(hero);
	path_ = hero.getPath(inputEvent.mouseButton.x, 
							inputEvent.mouseButton.y);
}