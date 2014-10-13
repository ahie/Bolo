#pragma once
#include "Renderable.h"

class UIElement : public Renderable
{
public:
	friend class UI;
	UIElement(bool visible, bool clickable) :
		visible_(visible),
		clickable_(clickable) {}
	virtual ~UIElement() {}
	virtual void onClick() = 0;
	virtual bool handleInput(sf::Event) { return false; }
protected:
	bool visible_;
	bool clickable_;
};
