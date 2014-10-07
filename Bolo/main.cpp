#include "World.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Bolo");
	World world;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear(sf::Color::Black);
		world.render(window);
		window.display();
	}

	return 0;
}
