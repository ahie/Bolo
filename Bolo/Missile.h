#pragma once
#include "Attack.h"
#include "Renderable.h"

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
		color_(sf::Color(100, 0, 100)) {}
	~Missile() {}
	void advance(float dt) { pos_ += speed_ * dirVec_; }
	virtual void render(sf::RenderWindow& window)
	{
		sf::CircleShape missile(hitRadius_);
		missile.setFillColor(color_);
		missile.setOrigin(hitRadius_, hitRadius_);
		missile.setPosition(sf::Vector2f(pos_.x - pos_.y, (pos_.x + pos_.y) / 2.0f));
		window.draw(missile);
	}
private:
	float speed_;
	sf::Vector2f dirVec_;
	// has graphics
	sf::Color color_;
};
