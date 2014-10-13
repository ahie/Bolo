#include "UI.h"
#include "InputHandler.h"
#include "Level.h"
#include "Monster.h"
#include "Hero.h"
#include "HeroDeath.h"
#include <SFML\System\Clock.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Bolo");
	sf::Clock deltaClock;

	UI gameUI;
	HeroDeath heroDeath;
	gameUI.addElement(&heroDeath);

	Hero* hero = new Hero;
	hero->addObserver(&heroDeath);
	hero->setPosition(sf::Vector2f(50, 50));
	Monster* monster = new Monster;
	MonsterAI ai;
	monster->setAI(&ai);
	monster->setPosition(sf::Vector2f(40, 100));

	Terrain terrain(100,100);
	Level level;
	level.setTerrain(&terrain);
	level.addEntity(hero);
	level.addEntity(monster);

	hero->setLevel(&level);
	monster->setLevel(&level);

	InputHandler iHandler;
	iHandler.setUI(&gameUI);
	iHandler.setHero(hero);

	sf::View view;
	view.setCenter(hero->getPos());
	view.setSize(sf::Vector2f(400, 600));

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			iHandler.handleInput(window,event);
		}
		sf::Time dt = deltaClock.restart();
		level.update(dt.asSeconds());

		view.setCenter(hero->getPos());
		view.setSize(sf::Vector2f(400, 600));
		window.setView(view);

		window.clear(sf::Color::Black);
		level.render(window);
		gameUI.render(window);
		window.display();
	}

	return 0;
}
