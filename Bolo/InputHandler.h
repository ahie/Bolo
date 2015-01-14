#pragma once
#include "UI.h"
#include "Hero.h"
#include "EntityEvent.h"
#include "Game.h"
#include "UIFunctions.h"

// Chain of responsibility:
// If input event not handled by UI, 
// give it to the player controlled character (hero).
class InputHandler
{
public:
	InputHandler(Game* game) : game_(game) {}
	~InputHandler() {}
	void handleInput(sf::RenderWindow& window, sf::Event event)
	{
		if (event.type == sf::Event::Closed)
			UIFuncs::exitGame();

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			UIFuncs::toggleOverlayMenu();

		if (game_->getUI() != nullptr 
			&& !game_->getUI()->handleInput(event)
			&& game_->getHero() != nullptr) {

			// Convert sf::Event to EntityEvent
			// Set event's mouse coordinates relative to view 
			// and transform from isometric to cartesian.
			if (event.type == sf::Event::MouseButtonPressed) {
				sf::Vector2f coordPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
				sf::Vector2f clickPos = sf::Vector2f((coordPos.x + 2.0f*coordPos.y) / 2.0f, (2.0f*coordPos.y - coordPos.x) / 2.0f);

				// Send EntityEvent.
				if (event.mouseButton.button == sf::Mouse::Left) 
					game_->getHero()->handleInput(EntityEvent(true, EntityEvent::Click::LEFT, clickPos));
				else if (event.mouseButton.button == sf::Mouse::Right) 
					game_->getHero()->handleInput(EntityEvent(true, EntityEvent::Click::RIGHT, clickPos));
			}
		}
	}
private:
	Game* game_;
};
