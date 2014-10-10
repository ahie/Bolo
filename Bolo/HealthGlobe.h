#include "Oberserver.h"
#include "Hero.h"
#include "UI.h"

class HealthGlobe : public UIElement, Observer
{
public:
	HealthGlobe(Hero* hero) : 
		UIElement(true,false), 
		hpPercent_(0.0f), 
		hero_(hero) {}
	virtual void onNotify(Subject* subject, Event event)
	{
		if (event == HERO_HEALTH_CHANGED && subject == hero_)
		{
			hpPercent_ = hero_->getPercentHP();
		}
	}
	virtual void render(sf::RenderWindow& window) 
	{
		if (visible_)
		{
			sf::RectangleShape bound(sf::Vector2f(5, 5));
			bound.setFillColor(sf::Color(255,0,0));
			bound.setOutlineColor(sf::Color(0, 0, 0));
			bound.setOutlineThickness(0.1);
			bound.setPosition(window.mapPixelToCoords(sf::Vector2i(50,50)));
			sf::RectangleShape hp(sf::Vector2f(5, 5 * hpPercent_));
			hp.setFillColor(sf::Color(0, 255, 0));
			bound.setPosition(window.mapPixelToCoords(sf::Vector2i(50, 50)));
			window.draw(bound);
			window.draw(hp);

		}
	}
	virtual void onClick() {}
protected:
	float hpPercent_;
	Hero* hero_;
};