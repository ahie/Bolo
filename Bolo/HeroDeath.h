#pragma once
#include "Oberserver.h"
#include "Hero.h"
#include "UIElement.h"

class HeroDeath : public UIElement, public Observer
{
public:
	HeroDeath() :
		UIElement(false, false) {}
	~HeroDeath() {}
	virtual void onNotify(Subject* subject, Event event) {
		if (event == HERO_DIED)
			visible_ = true;
	}
	virtual void render(sf::RenderWindow& window) {
		if (visible_) {
			// TODO: proper centering, load font somewhere else
			// Exit to menu button.
			sf::Text text;
			sf::Font font;
			font.loadFromFile("Resources/Fonts/diablo_h.ttf");
			text.setFont(font);
			text.setString("YOU HAVE DIED.");
			text.setCharacterSize(35);
			text.setColor(sf::Color::Yellow);
			text.setPosition(window.mapPixelToCoords(sf::Vector2i(150, 150)));
			window.draw(text);
			text.setString("YOUR DEEDS OF VALOR WILL BE REMEMBERED.");
			text.setCharacterSize(20);
			text.setPosition(window.mapPixelToCoords(sf::Vector2i(50, 275)));
			window.draw(text);
		}
	}
};