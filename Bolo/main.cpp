#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include "Tile.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Marjaisa");
	sf::Image image;
	sf::Texture texture;
	image.loadFromFile("C:\\Users\\Aleksi\\Desktop\\MM\\Marjaisa\\Marjaisa\\Resources\\Tilesets\\Cave.png");
	image.createMaskFromColor(sf::Color(255, 255, 255), 0);
	texture.loadFromImage(image);

	std::vector<Tile> tiles;
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			if (i == 0 && j == 0)
				tiles.push_back(Tile((float)i*TILE_WIDTH, (float)j*TILE_HEIGHT, &texture, 10, 0));
			else if (j == 0)
				tiles.push_back(Tile((float)i*TILE_WIDTH, (float)j*TILE_HEIGHT, &texture, 9, 0));
			else if (i == 0)
				tiles.push_back(Tile((float)i*TILE_WIDTH, (float)j*TILE_HEIGHT, &texture, 8, 0));

			else if (rand() % 20 < 1)
				tiles.push_back(Tile((float)i*TILE_WIDTH, (float)j*TILE_HEIGHT, &texture, 11, 2));
			else if (rand() % 20 < 1)
				tiles.push_back(Tile((float)i*TILE_WIDTH, (float)j*TILE_HEIGHT, &texture, 13, 2));
			else if (rand() % 20 < 3)
				tiles.push_back(Tile((float)i*TILE_WIDTH, (float)j*TILE_HEIGHT, &texture, 6, 0));
			else
				tiles.push_back(Tile((float)i*TILE_WIDTH, (float)j*TILE_HEIGHT, &texture, 6, 5));

		}
	}

	sf::View view(sf::Vector2f(0, 250), sf::Vector2f(800, 600));
	window.setView(view);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		for each (auto t in tiles)
		{
			t.render(window);
		}

		window.display();
	}

	return 0;
}