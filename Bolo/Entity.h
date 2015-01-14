#pragma once
#include "Subject.h"
#include "Renderable.h"
#include "EntityState.h"
#include "Attack.h"
#include "Animation.h"
#include "Faction.h"
#include "EntityEvent.h"
#include "Item.h"

#include <string>
#include <unordered_map>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

class Level;
class NavGraph;

enum Anim { STAND, WALK, ATTACK, DEATH };

class Entity : public Subject, public Renderable
{
public:
	Entity(std::string name, Faction faction, AttackDescriptor attack);
	virtual ~Entity();

	virtual void setLevel(Level* level);
	virtual void setHP(float hp);
	virtual void setColor(sf::Color color);
	virtual void setName(std::string name);
	virtual void setPosition(sf::Vector2f pos);
	
	float getPercentHP() const;
	float getDamage() const;
	float getHP() const;
	sf::Vector2f getPos() const;
	sf::Vector2f getIsometricPos() const;
	std::vector<sf::Vector2f> getPath(float x, float y);
	float getAttackSpeed() const;
	float getAnimLength();
	bool isAlive() const;
	Faction getFaction() const;
	float getArmor();
	float getHPRegen();

	virtual void update(float dt);
	bool checkCollision(sf::Vector2f at, float radius) const;
	virtual void render(sf::RenderWindow& window);
	virtual void handleInput(EntityEvent event);
	virtual void move(sf::Vector2f to, float& dt);
	virtual void attack(sf::Vector2f direction);
	virtual void castSpell(sf::Vector2f direction);
	virtual void damage(Attack* attack);
	virtual void kill();
	virtual RenderableSprite requestSprite();

	void updateOrientation(sf::Vector2f dir);
	virtual void setAnimation(Anim animation);

protected:
	Level* getLevel() const;
	EntityState* getState() const;
	void setState(EntityState* state);
	void addAnimation(Anim type, Animation* pointerToAnim);
	void setMaxHP(float maxhp);
	void addHP(float hp);
	void addDamage(float damage);
	void applyModifier(const std::pair<ModType, float>& mod);

private:
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
	float armor_;
	float hpRegen_;
	float hp_;
	float maxhp_;
	bool alive_;

	Orientation orient_;
	float animTime_;
	Animation* activeAnimation_;
	std::unordered_map<Anim, Animation*> animations_;

	Level* level_;
	NavGraph* navGraph_;
};
