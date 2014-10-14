#pragma once
#include "Subject.h"
#include "Renderable.h"
#include "EntityState.h"
#include "Attack.h"
#include "Faction.h"

#include <string>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

class Level;
class NavGraph;

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
	virtual void handleInput(sf::Event inputEvent);
	virtual void move(sf::Vector2f to, float& dt);
	virtual void attack(sf::Vector2f direction);
	virtual void damage(Attack* attack);
	virtual void kill();
	virtual float getPercentHP();
	virtual sf::Vector2f getPos() const;
	virtual std::vector<sf::Vector2f> getPath(float x, float y);
	virtual bool checkCollision(sf::Vector2f at, float radius) const;
	virtual bool isAlive() { return alive_; }
	virtual Faction Entity::faction() const;
protected:
	Entity();

	std::string name_;
	EntityState* state_;
	sf::Color color_;
	sf::Vector2f pos_;
	AttackDescriptor aDescription_;
	float collisionRadius_;
	float moveSpeed_;
	float hp_;
	float maxhp_;
	bool alive_;

	Level* level_;
	NavGraph* navGraph_;

	Faction faction_;
};
