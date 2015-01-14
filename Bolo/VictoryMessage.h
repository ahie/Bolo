#pragma once
#include "Observer.h"
#include "Hero.h"
#include "UIElement.h"
#include "UIButton.h"
#include "UIFunctions.h"

class VictoryMessage : public UIElement, public Observer
{
public:
	VictoryMessage(Game* game) :
		UIElement(false, false), font_(sf::Font()), exitGame_(nullptr), game_(game)
	{
		font_.loadFromFile("Resources/Fonts/diablo.ttf");
		exitGame_ = new UIButton(sf::Vector2i(200, 275), "EXIT GAME", "diablo.ttf", 35, UIFuncs::exitGame);
	}
	~VictoryMessage()
	{
		delete exitGame_;
	}
	virtual void onNotify(Subject* subject, Event event) {
		if (event == DIABLO_KILLED) {
			visible_ = true;
			clickable_ = true;
			game_->disableGame();
		}
	}
	virtual void render(sf::RenderWindow& window) {
		if (visible_) {
			// TODO: sort this mess out :_D?
			sf::Text text;
			text.setFont(font_);
			text.setString("YOU HAVE TRIUMPHED OVER");
			text.setCharacterSize(35);
			text.setColor(sf::Color::Yellow);
			float width = text.getLocalBounds().width;
			float height = text.getLocalBounds().height;
			text.setPosition(window.mapPixelToCoords(sf::Vector2i((640 - width) / 2.f, 50)));
			window.draw(text);
			text.setString("EVIL!");
			text.setCharacterSize(35);
			width = text.getLocalBounds().width;
			text.setPosition(window.mapPixelToCoords(sf::Vector2i((640 - width) / 2.f, 50 + height + 10)));
			window.draw(text);
			text.setString("THE CONTINUED SURVIVAL OF MANKIND");
			text.setCharacterSize(20);
			width = text.getLocalBounds().width;
			text.setPosition(window.mapPixelToCoords(sf::Vector2i((640 - width) / 2.f, 175)));
			window.draw(text);
			text.setString("IS YOUR LEGACY!");
			text.setCharacterSize(20);
			width = text.getLocalBounds().width;
			height = text.getLocalBounds().height;
			text.setPosition(window.mapPixelToCoords(sf::Vector2i((640 - width) / 2.f, 175 + height + 5)));
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