#pragma once
#include "Subject.h"
#include "Renderable.h"
#include "EntityState.h"
#include "Attack.h"
#include "Faction.h"
#include "EntityEvent.h"

#include <string>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

class Level;
class NavGraph;

enum Orientation { S, SW, W, NW, N, NE, E, SE };
enum Anim { STAND, WALK, ATTACK, DEATH };

struct Animation
{
	Animation(int width, sf::Image* img, float frameRate = 6.0f) :
	frameWidth(width), sheetimage(img), framesPerSecond(frameRate)
	{
		spritesheet.loadFromImage(*sheetimage);
		frameCount = (spritesheet.getSize().x / frameWidth);
		totalTime = ((float)frameCount) / framesPerSecond;
		sprite.setTexture(spritesheet);
	}
	int frameWidth;
	int frameCount;
	float framesPerSecond;
	float totalTime;
	sf::Image* sheetimage;
	sf::Texture spritesheet;
	sf::Sprite sprite;
	void setSpeed(float speed) { totalTime = speed; }
	float getLength() { return totalTime; }
	float getDims() { return (float)frameWidth; }
	sf::Sprite getSprite(float& time, Orientation orient)
	{
		if (time > totalTime) time = 0.0f;
		sprite.setTextureRect(sf::IntRect((int)((time/totalTime)*frameCount)*frameWidth, frameWidth*orient, frameWidth, frameWidth));
		return sprite;
	}
};

class Entity : public Subject, public Renderable
{
public:
	virtual ~Entity();
	virtual void setLevel(Level* level);
	virtual void setColor(sf::Color color);
	virtual void setName(std::string name);
	virtual void setPosition(sf::Vector2f pos);
	virtual void update(float dt);
	virtual void render(sf::RenderWindow& window);
	virtual void handleInput(EntityEvent event);
	virtual void move(sf::Vector2f to, float& dt);
	virtual void attack(sf::Vector2f direction);
	virtual void damage(Attack* attack);
	virtual void kill();
	virtual float getPercentHP();
	virtual sf::Vector2f getPos() const;
	virtual sf::Vector2f getIsometricPos() const;
	virtual std::vector<sf::Vector2f> getPath(float x, float y);
	virtual bool checkCollision(sf::Vector2f at, float radius) const;
	virtual bool isAlive() { return alive_; }
	virtual Faction Entity::faction() const;
	virtual float getAttackSpeed() const { return attackSpeed_; }

	void updateOrientation(sf::Vector2f dir);
	float getAnimLength() 
	{
		if (activeAnimation_ == nullptr) return 0.0f;
		return activeAnimation_->getLength();
	}

	// test
	virtual void setAnimation(Anim a) 
	{  
		animTime_ = 0.0f;
		if (a == WALK)
			activeAnimation_ = walkAnimation_;
		else if (a == STAND)
			activeAnimation_ = standAnimation_;
		else if (a == ATTACK) {
			activeAnimation_ = attackAnimation_;
			if (activeAnimation_ != nullptr)
				activeAnimation_->setSpeed(attackSpeed_);
		}
		else if (a == DEATH)
			activeAnimation_ = deathAnimation_;
	}
protected:
	Entity();
	AttackDescriptor aDescription_;
	Faction faction_;

	std::string name_;
	EntityState* state_;
	sf::Color color_;
	sf::Vector2f pos_;
	float collisionRadius_;
	float moveSpeed_;
	float attackSpeed_;
	float hp_;
	float maxhp_;
	bool alive_;

	Orientation orient_;
	// test
	Animation* standAnimation_;
	Animation* walkAnimation_;
	Animation* attackAnimation_;
	Animation* deathAnimation_;
	Animation* activeAnimation_;
	float animTime_;

	Level* level_;
	NavGraph* navGraph_;
};
