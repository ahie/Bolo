#include "Game.h"
#include "InputHandler.h"
#include <SFML/System/Clock.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "Bolo", sf::Style::Titlebar | sf::Style::Close);
	window.setVerticalSyncEnabled(true);
	sf::Clock deltaClock;

	Game* game = new Game();
	InputHandler iHandler(game);

	// Game loop
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event)) iHandler.handleInput(window,event);
		game->update(deltaClock.restart().asSeconds());
		game->render(window);
	}

	return 0;
}
