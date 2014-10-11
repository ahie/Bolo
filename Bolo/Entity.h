#pragma once
#include "Subject.h"
#include "Renderable.h"
#include "EntityState.h"
#include "NavGraph.h"

#include <string>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

class Entity : public Subject, Renderable
{
public:
	Entity();
	~Entity();

	virtual void setNavGraph(NavGraph* navGraph);
	virtual void setColor(sf::Color color);
	virtual void setName(std::string name);
	virtual void update(float dt) = 0;
	virtual void render(sf::RenderWindow& window);
	virtual void handleInput(sf::Event inputEvent);
	virtual void move(sf::Vector2f to, float& dt);
	virtual float getPercentHP();
	virtual sf::Vector2f getPos() const;
	virtual std::vector<sf::Vector2f> getPath(float x, float y);
protected:
	std::string name_;
	NavGraph* navGraph_;
	EntityState* state_;
	sf::Color color_;
	sf::Vector2f pos_;
	float moveSpeed_;
	float hp_;
	float maxhp_;
};

