#pragma once
#include "Oberserver.h"
#include "Hero.h"
#include "UI.h"

class HeroDeath : public UIElement, public Observer
{
public:
	HeroDeath() :
		UIElement(false, false) {}
	~HeroDeath() {}
	virtual void onNotify(Subject* subject, Event event) {
		visible_ = true;
	}
	virtual void render(sf::RenderWindow& window) {
		// TODO: proper centering, load font somewhere else
		// Exit to menu button.
		sf::Text text;
		sf::Font font;
		font.loadFromFile("diablo_h.ttf");
		text.setFont(font);
		text.setString("YOU HAVE DIED.");
		text.setCharacterSize(34);
		text.setColor(sf::Color::Yellow);
		text.setPosition(window.mapPixelToCoords(sf::Vector2i(100, 150)));
		window.draw(text);
		text.setString("YOUR DEEDS OF VALOR WILL BE");
		text.setCharacterSize(20);
		text.setPosition(window.mapPixelToCoords(sf::Vector2i(30, 400)));
		window.draw(text);
		text.setString("REMEMBERED.");
		text.setPosition(window.mapPixelToCoords(sf::Vector2i(250, 425)));
		window.draw(text);
	}
	virtual void onClick() {}
};