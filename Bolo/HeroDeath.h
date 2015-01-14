#pragma once
#include "Observer.h"
#include "Hero.h"
#include "UIElement.h"
#include "UIButton.h"
#include "UIFunctions.h"

class HeroDeath : public UIElement, public Observer
{
public:
	HeroDeath(Game* game) :
		UIElement(false, false), font_(sf::Font()), exitGame_(nullptr), game_(game)
	{
		font_.loadFromFile("Resources/Fonts/diablo.ttf");
		exitGame_ = new UIButton(sf::Vector2i(200, 275), "EXIT GAME", "diablo.ttf", 35, UIFuncs::exitGame);
	}
	~HeroDeath() 
	{
		delete exitGame_;
	}
	virtual void onNotify(Subject* subject, Event event) {
		if (event == HERO_DIED) {
			visible_ = true;
			clickable_ = true;
			game_->disableGame();
		}
	}
	virtual void render(sf::RenderWindow& window) {
		if (visible_) {
			// TODO: proper centering
			sf::Text text;
			text.setFont(font_);
			text.setString("YOU HAVE DIED.");
			text.setCharacterSize(35);
			text.setColor(sf::Color::Yellow);
			text.setPosition(window.mapPixelToCoords(sf::Vector2i(150, 50)));
			window.draw(text);
			text.setString("YOUR DEEDS OF VALOR WILL BE REMEMBERED.");
			text.setCharacterSize(20);
			text.setPosition(window.mapPixelToCoords(sf::Vector2i(50, 175)));
			window.draw(text);
			exitGame_->render(window);
		}
	}
	virtual bool handleInput(sf::Event event) 
	{ 
		if (clickable_) 
			return exitGame_->handleInput(event);
		else return false;
	}
private:
	sf::Font font_;
	UIButton* exitGame_;
	Game* game_;
};