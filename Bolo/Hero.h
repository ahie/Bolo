#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include "HeroState.h"
#include "Renderable.h"
#include "NavGraph.h"
#include "Subject.h"

class Hero: public Subject, Renderable
{
public:
	Hero();
	~Hero();

	void setNavGraph(NavGraph* navGraph);
	void update(float dt);
	void render(sf::RenderWindow& window);
	void handleInput(sf::Event inputEvent);
	void setColor(sf::Color color);
	void move(sf::Vector2f to, float& dt);

	float getPercentHP();
	sf::Vector2f getPos() const;
	std::vector<sf::Vector2f> getPath(float x, float y);
private:
	NavGraph* navGraph_;
	HeroState* state_;
	sf::Color color_;
	sf::Vector2f pos_;
	float moveSpeed_;
	float hp_;
	float maxhp_;
};

