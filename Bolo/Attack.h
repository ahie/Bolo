#pragma once
#include "Faction.h"

#include <SFML\System\Vector2.hpp>

enum AttackClass { MELEE, MISSILE, SPELL };
enum AttackType { AOE, SINGLE_TARGET };
enum DamageType { PURE, FIRE, LIGHTNING, CHAOS };

class Attack
{
public:
	Attack(AttackType atype, 
		DamageType dtype, 
		float dmg, float hitrad, 
		sf::Vector2f pos,
		Faction source) :
			atckType_(atype),
			dmgType_(dtype),
			damage_(dmg),
			hitRadius_(hitrad),
			pos_(pos),
			belongsTo_(source){}
	virtual ~Attack() {}
	sf::Vector2f getPos() { return pos_; }
	float getRadius() { return hitRadius_; }
	float getDamage() { return damage_; }
	AttackType getType() { return atckType_; }
	Faction belongsTo() { return belongsTo_; }
protected:
	Faction belongsTo_;
	AttackType atckType_;
	DamageType dmgType_;
	sf::Vector2f pos_;
	float damage_;
	float hitRadius_;
};

struct AttackDescriptor
{
	AttackDescriptor(float dmg, 
		float hitRad, 
		float mSpeed, 
		AttackClass aClass, 
		AttackType aType, 
		DamageType dType) :
			damage(dmg), 
			hitRadius(hitRad), 
			missileSpeed(mSpeed), 
			atckClass(aClass), 
			atckType(aType), 
			dmgType(dType) {}

	float damage;
	float hitRadius;
	float missileSpeed;
	AttackClass atckClass;
	AttackType atckType;
	DamageType dmgType;
};
