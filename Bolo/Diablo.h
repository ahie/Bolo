#pragma once
#include "Monster.h"

class DiabloAI;

// Class for end boss entity.
class Diablo : public Monster 
{
public:
	Diablo() : 
		Monster("Mega"), 
		spell_(AttackDescriptor(50.0f, 10.0f, 0.f, MISSILE, AOE, FIRE, "Fire.png"))
	{
		setName("Diablo");
		setMaxHP(1000.f);
		setHP(1000.f);
		setAI(new DiabloAI());
	}
	virtual ~Diablo() {}
	virtual void kill()
	{
		Monster::kill();
		notify(DIABLO_KILLED);
	}
	virtual void castSpell(sf::Vector2f dir)
	{
		float angleRandom = rand();
		float distRandom = rand() % 200;
		sf::Vector2f pos(getPos().x + sin(angleRandom) * distRandom, getPos().y + cos(angleRandom) * distRandom);
		sf::Vector2f vec(0, 0);
		getLevel()->addAttack(spell_, *this, pos, vec);
	}
	virtual RenderableSprite requestSprite() 
	{ 
		RenderableSprite diabloSprite = Monster::requestSprite();
		(diabloSprite.sprite).setColor(sf::Color(255, 0, 0));
		return diabloSprite;
	}
private:
	AttackDescriptor spell_;
};