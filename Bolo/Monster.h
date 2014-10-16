#pragma once
#include "Entity.h"
#include "MonsterAI.h"

class Monster : public Entity 
{
public:
	friend class MonsterAI;
	Monster() : ai_(nullptr) {
		faction_ = FOE; 

		//ANIM TESTING
		sf::Image* megawalk = new sf::Image();
		sf::Image* megastand = new sf::Image();
		sf::Image* megaattack = new sf::Image();
		sf::Image* megadeath = new sf::Image();
		megawalk->loadFromFile("Resources/Spritesheets/Monsters/Mega/walk.png");
		megastand->loadFromFile("Resources/Spritesheets/Monsters/Mega/stand.png");
		megaattack->loadFromFile("Resources/Spritesheets/Monsters/Mega/attack.png");
		megadeath->loadFromFile("Resources/Spritesheets/Monsters/Mega/death.png");
		megawalk->createMaskFromColor(sf::Color(0, 0, 0), 0);
		megastand->createMaskFromColor(sf::Color(0, 0, 0), 0);
		megaattack->createMaskFromColor(sf::Color(0, 0, 0), 0);
		megadeath->createMaskFromColor(sf::Color(0, 0, 0), 0);
		standAnimation_ = new Animation(160, megastand);
		walkAnimation_ = new Animation(160, megawalk);
		attackAnimation_ = new Animation(160, megaattack);
		deathAnimation_ = new Animation(160, megadeath);
	}
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