#pragma once
#include "UI.h"
#include "World.h"
#include <SFML\Window.hpp>
class InputHandler
{
public:
	InputHandler(UI* ui, World* world) :
	uiInterface_(ui), 
	worldInterface_(world) {}
	~InputHandler();
	void handleInput(sf::Window& window, sf::Event event)
	{

	}
private:
	UI* uiInterface_;
	World* worldInterface_;
};

