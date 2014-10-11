#pragma once
#include "Entity.h"

class Hero: public Entity
{
public:
	Hero() {}
	~Hero() {}
	void update(float dt)
	{
		EntityState* state = state_->update(*this, dt);
		if (state != nullptr) {
			delete state_;
			state_ = state;
			state_->enter(*this);
		}
	}
private:
	// has inventory --> inventory holds items
	// has equipped items
};
