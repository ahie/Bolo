#pragma once
#include <SFML\System\Vector2.hpp>

enum AttackType { AOE, SINGLE_TARGET };
enum DamageType { PURE, FIRE, LIGHTNING, CHAOS };

class Attack
{
public:
	Attack(AttackType atype, DamageType dtype, float dmg, float hitrad) :
		atckType_(atype),
		dmgType_(dtype),
		damage_(dmg),
		hitRadius_(hitrad) {}
	~Attack() {}
protected:
	AttackType atckType_;
	DamageType dmgType_;
	sf::Vector2f pos_;
	float damage_;
	float hitRadius_;
};

class Missile : public Attack
{
public:
	Missile(AttackType atype, DamageType dtype, float dmg, float hitrad, CollisionHandler handler) :
		Attack(atype, dtype, dmg, hitrad),
		cHandler_(handler) {}
	~Missile() {}
	void update(AttackHandler aHandler);
private:
	CollisionHandler cHandler_;
	void advance();
};
