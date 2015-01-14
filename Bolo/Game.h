#pragma once
#include "Renderable.h"

#include <string>
#include <unordered_map>
#include <vector>

class Level;
class UI;
class Hero;
class Observer;
class Item;
class MonsterAI;

using std::string;
using std::unordered_map;
using std::vector;

// Handles creation and destruction of objects.
// Handles state of game.
class Game : public Renderable
{
public:
	Game();
	~Game();

	void cleanUp();
	void newGame();
	void toggleOverlay();
	void returnToMenu();
	void update(float dt);
	virtual void render(sf::RenderWindow& window);

	// void swapLevel(new hero position?) { move hero to new level, set new active level }

	void enableGame();
	void disableGame();

	// getters for input handler
	UI* getUI();
	Hero* getHero();

private:
	void initGame(string file = "Resources/defaultGame.json");
	void deleteGameData();

	void setUI(UI* newUI);
	void setLevel(Level* newLevel);
	void setHero(Hero* hero);

	bool gameRunning_;

	UI* activeUI_;
	Level* activeLevel_;
	Hero* activeHero_;

	// Destruct these
	unordered_map<string, UI*> userInterfaces_;
	vector<Level*> levels_;
	vector<MonsterAI*> ais_;
	vector<Item*> items_;
};