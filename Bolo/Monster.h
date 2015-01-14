#pragma once
#include "Entity.h"
#include "MonsterAI.h"
#include "Level.h"
#include "TextureContainer.h"

class Monster : public Entity 
{
public:
	friend class MonsterAI;
	Monster(std::string name) : 
		Entity(name, FOE, AttackDescriptor(50.0f, 10.0f, 0.f, MELEE, SINGLE_TARGET, PURE)), 
		ai_(nullptr)
	{
		addAnimation(STAND, new Animation(160, TextureContainer::instance().getTexture("Resources/Spritesheets/Monsters/" + name + "/stand.png")));
		addAnimation(WALK, new Animation(160, TextureContainer::instance().getTexture("Resources/Spritesheets/Monsters/" + name + "/walk.png")));
		addAnimation(ATTACK, new Animation(160, TextureContainer::instance().getTexture("Resources/Spritesheets/Monsters/" + name + "/attack.png")));
		addAnimation(DEATH, new Animation(160, TextureContainer::instance().getTexture("Resources/Spritesheets/Monsters/" + name + "/death.png")));
		getState()->enter(*this);
	}
	virtual ~Monster() {}
	void setAI(MonsterAI* ai) { ai_ = ai; }
	virtual void kill() 
	{ 
		getLevel()->spawnItem(getPos());
		Entity::kill();
	}
	virtual void update(float dt)
	{
		if (!isAlive()) return;
		if(ai_ != nullptr) ai_->think(this);
		Entity::update(dt);
	}
private:
	MonsterAI* ai_;
};