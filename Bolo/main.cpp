#include "World.h"
#include <SFML\System\Clock.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Bolo");
	World world;
	sf::Clock deltaClock;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			world.handleInput(event);
		}
		window.clear(sf::Color::Black);
		sf::Time dt = deltaClock.restart();
		world.update(window, dt.asSeconds());
		world.render(window);
		window.display();
	}

	return 0;
}
