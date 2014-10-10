#pragma once
#include "Renderable.h"
#include <vector>

class UIElement: public Renderable
{
public:
	UIElement(bool visible, bool clickable):
	visible_(visible),
	clickable_(clickable) {}
	virtual ~UIElement() {}
	virtual void onClick() = 0;
protected:
	bool visible_;
	bool clickable_;
};

class UI: public Renderable
{
public:
	UI() {}
	~UI() {}
	void addElement(UIElement* elem)
	{
		UIElements_.push_back(elem);
	}
	virtual void render(sf::RenderWindow& window)
	{
		for (auto UIElement : UIElements_)
			UIElement->render(window);
	}
private:
	std::vector<UIElement*> UIElements_;
};

