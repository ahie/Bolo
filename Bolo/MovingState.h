#pragma once
#include "HeroState.h"
#include <vector>
class MovingState :
	public HeroState
{
public:
	MovingState();
	~MovingState();
	virtual void enter(Hero& hero);
	virtual void enter(Hero& hero, sf::Event inputEvent);
	virtual HeroState* update(Hero& hero, float dt);
	virtual HeroState* handleInput(Hero& hero, sf::Event inputEvent);
private:
	std::vector<sf::Vector2f> path_;
};
