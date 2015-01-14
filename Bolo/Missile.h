#pragma once
#include "Attack.h"
#include "Renderable.h"
#include "Animation.h"
#include "TextureContainer.h"

class Missile : public Attack, public Renderable
{
public:
	Missile(AttackDescriptor descriptor,
		Faction belongsTo, 
		sf::Vector2f pos,
		sf::Vector2f dir) :
			Attack(descriptor, belongsTo, pos),
			speed_(descriptor.missileSpeed),
			dirVec_(dir),
			orient_(getOrientation(dir)),
			animTime_(0.f) 
	{
		anim_ = new Animation(96, TextureContainer::instance().getTexture("Resources/Spritesheets/Missiles/" + descriptor.missileString));
	}
	~Missile() 
	{
		delete anim_;
	}
	void advance(float dt) 
	{ 
		pos_ += speed_ * dirVec_; 
		animTime_ += dt;
	}
	virtual sf::Vector2f getIsometricPos() 
	{ 
		return sf::Vector2f(pos_.x - pos_.y, (pos_.x + pos_.y) / 2.0f); 
	}
	virtual void render(sf::RenderWindow& window) {}
	virtual RenderableSprite requestSprite() 
	{ 
			sf::Sprite sprite = anim_->getSprite(animTime_, orient_);
			sf::Vector2f pos = getIsometricPos();
			sprite.setPosition(pos.x - anim_->getDims() / 2.0f,
				pos.y - anim_->getDims() + 10.0f);
			return RenderableSprite(sprite, pos_);
	}
private:
	float speed_;
	sf::Vector2f dirVec_;

	// Is animated
	Animation* anim_;
	Orientation orient_;
	float animTime_;
};
