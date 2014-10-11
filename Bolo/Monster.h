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
		Entity::update(dt);
	}
private:
	MonsterAI* ai_;
};