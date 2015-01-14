#pragma once
#include "UIElement.h"

class UIButton : public UIElement
{
public:
	UIButton(sf::Vector2i pos, std::string text, 
		std::string font, int fontSize, 
		void(*clickFunc)(), sf::Color color = sf::Color::Yellow) :
			UIElement(true, true),
			pos_(pos),
			clickFunc_(clickFunc) 
	{
		buttonFont_.loadFromFile("Resources/Fonts/" + font);
		buttonText_.setFont(buttonFont_);
		buttonText_.setString(text);
		buttonText_.setCharacterSize(fontSize);
		buttonText_.setColor(color);
		size_ = sf::Vector2f(buttonText_.getGlobalBounds().width, buttonText_.getGlobalBounds().height * 2.0f);
	}
	virtual ~UIButton() {}
	virtual bool handleInput(sf::Event event)
	{
		if (/*clicked*/
			event.type == sf::Event::MouseButtonPressed &&
			event.mouseButton.button == sf::Mouse::Left &&
			(event.mouseButton.x >= pos_.x && 
			event.mouseButton.x <= pos_.x + size_.x)
			&& (event.mouseButton.y >= pos_.y && 
			event.mouseButton.y <= pos_.y + size_.y)) {

			clickFunc_();
			return true;

		}
		return false;
	}
	virtual void render(sf::RenderWindow& window)
	{
		sf::RectangleShape rectangle;
		rectangle.setSize(size_);
		rectangle.setFillColor(sf::Color(0, 0, 0));
		rectangle.setPosition(window.mapPixelToCoords(pos_));
		window.draw(rectangle);
		buttonText_.setPosition(window.mapPixelToCoords(pos_));
		window.draw(buttonText_);
	}
private:
	UIButton();

	sf::Text buttonText_;
	sf::Font buttonFont_;
	sf::Vector2i pos_;
	sf::Vector2f size_;

	void(*clickFunc_)();
};