#pragma once
#include "UIElement.h"
#include <vector>

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
		for (auto uiElem : UIElements_) {
			if (uiElem->visible_)
				uiElem->render(window);
		}
	}
private:
	std::vector<UIElement*> UIElements_;
};

