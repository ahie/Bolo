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

EntityState* MovingState::handleInput(Entity& hero, sf::Event inputEvent)
{
	if (inputEvent.type == sf::Event::MouseButtonPressed) {
		if (inputEvent.mouseButton.button == sf::Mouse::Left) {
			path_ = hero.getPath(inputEvent.mouseButton.x,
									inputEvent.mouseButton.y);
		}
	}
	return nullptr;
}

EntityState* MovingState::update(Entity& hero, float dt)
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

void MovingState::enter(Entity& hero)
{
	hero.setColor(sf::Color(0, 0, 255));
}

void MovingState::enter(Entity& hero, sf::Event inputEvent)
{
	this->enter(hero);
	path_ = hero.getPath(inputEvent.mouseButton.x, 
							inputEvent.mouseButton.y);
}