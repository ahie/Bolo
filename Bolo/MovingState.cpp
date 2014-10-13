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

EntityState* MovingState::handleInput(Entity& entity, sf::Event inputEvent)
{
	if (inputEvent.type == sf::Event::MouseButtonPressed) {
		if (inputEvent.mouseButton.button == sf::Mouse::Right) {
			path_ = entity.getPath(inputEvent.mouseButton.x,
									inputEvent.mouseButton.y);
		}
		if (inputEvent.mouseButton.button == sf::Mouse::Left) {
			sf::Vector2f attackDirection = normalize(sf::Vector2f(inputEvent.mouseButton.x, inputEvent.mouseButton.y) - entity.getPos());
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
	entity.setColor(sf::Color(0, 0, 255));
}
