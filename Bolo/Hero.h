#pragma once
#include "Entity.h"

class Hero: public Entity
{
public:
	Hero() {}
	~Hero() {}
private:
	// has inventory --> inventory holds items
	// has equipped items
};
