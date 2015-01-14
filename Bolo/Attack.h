#pragma once
#include "Faction.h"

#include <SFML/System/Vector2.hpp>
#include <string>

enum AttackClass { MELEE, MISSILE, SPELL };
enum AttackType { AOE, SINGLE_TARGET };
enum DamageType { PURE, FIRE, LIGHTNING, CHAOS };

struct AttackDescriptor
{
	AttackDescriptor(float dmg,
	float hitRad,
	float mSpeed,
	AttackClass aClass,
	AttackType aType,
	DamageType dType,
	std::string string = "") :
		damage(dmg),
		hitRadius(hitRad),
		missileSpeed(mSpeed),
		atckClass(aClass),
		atckType(aType),
		dmgType(dType),
		missileString(string) {}

	float damage;
	float hitRadius;
	float missileSpeed;
	AttackClass atckClass;
	AttackType atckType;
	DamageType dmgType;
	std::string missileString;
};

class Attack
{
public:
	Attack(AttackDescriptor descriptor, Faction belongsTo, sf::Vector2f pos) :
		descriptor_(descriptor),
		belongsTo_(belongsTo),
		pos_(pos) {}
	virtual ~Attack() {}
	sf::Vector2f getPos() { return pos_; }
	float getRadius() { return descriptor_.hitRadius; }
	float getDamage() { return descriptor_.damage; }
	AttackType getType() { return descriptor_.atckType; }
	Faction belongsTo() { return belongsTo_; }
protected:
	AttackDescriptor descriptor_;
	Faction belongsTo_;
	sf::Vector2f pos_;
};
