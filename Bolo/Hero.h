#pragma once
#include "Entity.h"

class Hero: public Entity
{
public:
	Hero() { faction_ = FRIEND; }
	~Hero() {}
	void kill()
	{
		notify(HERO_DIED);
	}
private:
	// has inventory --> inventory holds items
	// has equipped items
};
