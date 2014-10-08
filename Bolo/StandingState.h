#pragma once
#include "HeroState.h"

class StandingState :
	public HeroState
{
public:
	StandingState();
	~StandingState();
	virtual void enter(Hero& hero);
	virtual void enter(Hero& hero, sf::Event inputEvent);
	virtual HeroState* update(Hero& hero, float dt);
	virtual HeroState* handleInput(Hero& hero, sf::Event inputEvent);
};

