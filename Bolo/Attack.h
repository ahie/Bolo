#pragma once
#include "Faction.h"

#include <SFML\System\Vector2.hpp>

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

class Missile : public Attack, public Renderable
{
public:
	Missile(AttackType atype, 
		DamageType dtype, 
		float dmg, float 
		hitrad, sf::Vector2f pos,
		Faction source,
		float speed,
		sf::Vector2f dir) :
			Attack(atype, dtype, dmg, hitrad, pos, source),
			speed_(speed),
			dirVec_(dir),
			color_(sf::Color(100,0,100)) {}
	~Missile() {}
	void advance(float dt) { pos_ += speed_ * dirVec_; }
	virtual void render(sf::RenderWindow& window)
	{
		sf::CircleShape missile(hitRadius_);
		missile.setFillColor(color_);
		missile.setOrigin(hitRadius_, hitRadius_);
		missile.setPosition(pos_);
		window.draw(missile);
	}
private:
	float speed_;
	sf::Vector2f dirVec_;
	// has graphics
	sf::Color color_;
};
