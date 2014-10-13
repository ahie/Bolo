#pragma once
#include "UIElement.h"
#include <vector>

class UI: public Renderable
{
public:
	UI() {}
	virtual ~UI() {}
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
	virtual bool handleInput(sf::Event inputEvent)
	{
		// reverse iteration on UIElements since back() is the topmost element
		for (std::vector<UIElement*>::reverse_iterator rit = UIElements_.rbegin();
			rit != UIElements_.rend(); ++rit) {
			if ((*rit)->handleInput(inputEvent))
				return true;
		}
		return false;
	}
private:
	std::vector<UIElement*> UIElements_;
};

