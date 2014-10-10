#pragma once
#include "UI.h"
#include "World.h"

class InputHandler
{
public:
	InputHandler(UI* ui, World* world) :
	uiInterface_(ui), 
	worldInterface_(world) {}
	~InputHandler(){}
	void handleInput(sf::RenderWindow& window, sf::Event event)
	{
		if (event.type == sf::Event::MouseButtonPressed) {
			sf::Vector2f coord_pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
			event.mouseButton.x = coord_pos.x;
			event.mouseButton.y = coord_pos.y;
			worldInterface_->handleInput(event);
		}
	}
private:
	UI* uiInterface_;
	World* worldInterface_;
};
