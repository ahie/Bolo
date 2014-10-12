#include "MovingState.h"
#include "StandingState.h"
#include "Hero.h"
#include <SFML\Graphics\Color.hpp>


MovingState::MovingState(Entity& entity, float x, float y) : 
	path_(entity.getPath(x, y)) {}


MovingState::~MovingState() {}

EntityState* MovingState::handleInput(Entity& entity, sf::Event inputEvent)
{
	if (inputEvent.type == sf::Event::MouseButtonPressed) {
		if (inputEvent.mouseButton.button == sf::Mouse::Right) {
			path_ = entity.getPath(inputEvent.mouseButton.x,
									inputEvent.mouseButton.y);
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
	entity.setColor(sf::Color(0, 0, 255));
}
