#pragma once
#include "UI.h"
#include "Level.h"

class GameState
{
public:
	GameState() : activeUI_(nullptr), activeLevel_(nullptr), activeHero_(nullptr) {}
	~GameState() {}
	void setUI(UI* newUI) { activeUI_ = newUI; }
	void setLevel(Level* newLevel) { activeLevel_ = newLevel; }
	void setHero(Hero* hero) { activeHero_ = hero; }
	UI* getUI() { return activeUI_; }
	Hero* getHero() { return activeHero_; }
	void update(float dt)
	{
		if (activeLevel_ != nullptr)
			activeLevel_->update(dt);
	}
	virtual void render(sf::RenderWindow& window)
	{
		if (activeLevel_ != nullptr)
			activeLevel_->render(window);
		if (activeUI_ != nullptr)
			activeUI_->render(window);
	}
private:
	UI* activeUI_;
	Level* activeLevel_;
	Hero* activeHero_;
};