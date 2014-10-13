#pragma once
#include "Entity.h"
#include "MonsterAI.h"

class Monster : public Entity 
{
public:
	friend class MonsterAI;
	Monster() : ai_(nullptr) { faction_ = FOE; }
	~Monster() {}
	void setAI(MonsterAI* ai) { ai_ = ai; }
	virtual void update(float dt)
	{
		if (!alive_)
			return;
		ai_->think(this);
		Entity::update(dt);
	}
private:
	MonsterAI* ai_;
};