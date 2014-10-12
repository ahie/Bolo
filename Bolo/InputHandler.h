#pragma once
#include "UI.h"
#include "Hero.h"

// Chain of responsibility: 
// If input event not handled by ui, 
// give it to the player controlled character (hero).
class InputHandler
{
public:
	InputHandler() :
		ui_(nullptr), 
		hero_(nullptr) {}
	~InputHandler() {}
	void setUI(UI* ui) { ui_ = ui; }
	void setHero(Hero* hero) { hero_ = hero; }
	void handleInput(sf::RenderWindow& window, sf::Event event)
	{
		if (ui_ == nullptr) return;

		// Set event's mouse coordinates relative to view.
		if (event.type == sf::Event::MouseButtonPressed) {
			sf::Vector2f coord_pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
			event.mouseButton.x = coord_pos.x;
			event.mouseButton.y = coord_pos.y;
		}

		if (!ui_->handleInput(event) && hero_ != nullptr)
			hero_->handleInput(event);
	}
private:
	UI* ui_;
	Hero* hero_;
};
