#pragma once
#include "Observer.h"
#include "UIElement.h"
#include "Hero.h"

#include <string>

static sf::Text getDrawableText(sf::Font* font, std::string string, sf::Vector2f pos)
{
	sf::Text text;
	text.setFont(*font);
	text.setCharacterSize(20);
	text.setColor(sf::Color(255, 255, 255));
	text.setPosition(pos);
	text.setString(string);
	return text;
}

class HUD : public UIElement, public Observer
{
public:
	HUD(Hero* hero) :
		UIElement(true, false),
		hpPercent_(0.0f),
		font_(sf::Font()),
		hero_(hero) 
	{
		onNotify(hero_, HERO_HEALTH_CHANGED);
		onNotify(hero_, HERO_STAT_CHANGE);
		font_.loadFromFile("Resources/Fonts/diablo.ttf");
		backgroundTexture_.loadFromFile("Resources/UI/HUD.png");
		backgroundSprite_.setTexture(backgroundTexture_);
	}
	virtual void onNotify(Subject* subject, Event event)
	{
		if (event == HEALTH_CHANGED && subject == hero_) 
		{
			hpPercent_ = hero_->getPercentHP();
			if (hpPercent_ < 0.f) hpPercent_ = 0.0f;
		}
		if (event == HERO_STAT_CHANGE && subject == hero_) 
		{
			hpRegen_ = hero_->getHPRegen();
			armor_ = hero_->getArmor();
			damage_ = hero_->getDamage();
		}
	}
	virtual void render(sf::RenderWindow& window)
	{
		backgroundSprite_.setPosition(window.mapPixelToCoords(sf::Vector2i(0, 350)));
		window.draw(backgroundSprite_);

		// Draw healthbar
		sf::RectangleShape bound(sf::Vector2f(75, 25));
		bound.setFillColor(sf::Color(255, 0, 0));
		bound.setOutlineColor(sf::Color(0, 0, 0));
		bound.setOutlineThickness(4);
		bound.setPosition(window.mapPixelToCoords(sf::Vector2i(40, 410)));
		sf::RectangleShape hp(sf::Vector2f(75 * hpPercent_, 25));
		hp.setFillColor(sf::Color(0, 255, 0));
		hp.setPosition(window.mapPixelToCoords(sf::Vector2i(40, 410)));
		window.draw(bound);
		window.draw(hp);

		window.draw(getDrawableText(&font_, std::string("HEALTH:"), window.mapPixelToCoords(sf::Vector2i(35, 380))));
		window.draw(getDrawableText(&font_, std::string("DAMAGE: " + std::to_string(damage_)), window.mapPixelToCoords(sf::Vector2i(180, 420))));
		window.draw(getDrawableText(&font_, std::string("HPREGEN: " + std::to_string(hpRegen_)), window.mapPixelToCoords(sf::Vector2i(180, 400))));
		window.draw(getDrawableText(&font_, std::string("ARMOR: " + std::to_string(armor_)), window.mapPixelToCoords(sf::Vector2i(180, 380))));
	}
protected:
	// HUD font
	sf::Font font_;

	// HUD background
	sf::Texture backgroundTexture_;
	sf::Sprite backgroundSprite_;

	// stats to display
	float damage_;
	float hpRegen_;
	float armor_;
	float hpPercent_;

	// observed hero
	Hero* hero_;
};