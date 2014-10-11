#pragma once
#include "Entity.h"
#include "MonsterAI.h"

class Monster : public Entity 
{
public:
	Monster() {}
	~Monster() {}
	virtual void update(float dt)
	{
		ai_->think(this);
		EntityState* state = state_->update(*this, dt);
		if (state != nullptr) {
			delete state_;
			state_ = state;
			state_->enter(*this);
		}
	}
private:
	MonsterAI* ai_;
	// Has an AI
	// AI generates input events
};