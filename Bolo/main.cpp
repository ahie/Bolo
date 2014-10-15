#include "UI.h"
#include "InputHandler.h"
#include "Level.h"
#include "Monster.h"
#include "Hero.h"
#include "HeroDeath.h"
#include "Inventory.h"
#include "Item.h"
#include <SFML\System\Clock.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "Bolo");
	sf::Clock deltaClock;

	// ui, deathmessage
	UI gameUI;
	HeroDeath heroDeath;
	gameUI.addElement(&heroDeath);

	// entities
	Hero* hero = new Hero;
	hero->addObserver(&heroDeath);
	hero->setPosition(sf::Vector2f(50, 50));
	Monster* monster = new Monster;
	MonsterAI ai;
	monster->setAI(&ai);
	monster->setPosition(sf::Vector2f(140, 100));

	// inventory
	sf::Texture inventoryTexture;
	sf::Sprite inventorySprite;
	inventoryTexture.loadFromFile("Inventory.bmp");
	inventorySprite.setTexture(inventoryTexture);
	Inventory inventory(&inventorySprite, hero);
	gameUI.addElement(&inventory);

	// items
	sf::Image weaponImage;
	sf::Texture weaponTexture;
	sf::Sprite weaponSprite;
	weaponImage.loadFromFile("weapon.bmp");
	weaponImage.createMaskFromColor(sf::Color(0, 0, 0), 150);
	weaponTexture.loadFromImage(weaponImage);
	weaponSprite.setTexture(weaponTexture);

	sf::Image helmetImage;
	sf::Texture helmetTexture;
	sf::Sprite helmetSprite;
	helmetImage.loadFromFile("helmet.bmp");
	helmetImage.createMaskFromColor(sf::Color(0,0,0),150);
	helmetTexture.loadFromImage(helmetImage);
	helmetSprite.setTexture(helmetTexture);

	Item helmet(&helmetSprite, HELMET, 2, 2);
	Item weapon(&weaponSprite, WEAPON, 2, 3);
	hero->loot(&helmet);
	hero->loot(&weapon);


	// terrain
	Terrain terrain(10,10);
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
	view.setSize(sf::Vector2f(640, 480));

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
		view.setSize(sf::Vector2f(640, 480));
		window.setView(view);

		window.clear(sf::Color::Black);
		level.render(window);
		gameUI.render(window);
		window.display();
	}

	return 0;
}
