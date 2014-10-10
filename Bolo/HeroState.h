#pragma once
#include <SFML\Window\Event.hpp>

class Hero;

class HeroState
{
public:
	HeroState() {}
	virtual ~HeroState() {}
	virtual void enter(Hero& hero) = 0;
	virtual void enter(Hero& hero, sf::Event inputEvent) = 0;
	virtual HeroState* update(Hero& hero, float dt) = 0;
	virtual HeroState* handleInput(Hero& hero, sf::Event inputEvent) = 0;
};

