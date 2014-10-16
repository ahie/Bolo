#pragma once
#include "UI.h"
#include "Hero.h"
#include "EntityEvent.h"

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

		if (!ui_->handleInput(event) && hero_ != nullptr) {
			// Set event's mouse coordinates relative to view.
			if (event.type == sf::Event::MouseButtonPressed) {
				sf::Vector2f coord_pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
				sf::Vector2f clickPos = sf::Vector2f((coord_pos.x + 2.0f*coord_pos.y) / 2.0f, (2.0f*coord_pos.y - coord_pos.x) / 2.0f);
				if (event.mouseButton.button == sf::Mouse::Left) hero_->handleInput(EntityEvent(true, EntityEvent::Click::LEFT, clickPos));
				else if (event.mouseButton.button == sf::Mouse::Right) hero_->handleInput(EntityEvent(true, EntityEvent::Click::RIGHT, clickPos));
			}
		}
	}
private:
	UI* ui_;
	Hero* hero_;
};
