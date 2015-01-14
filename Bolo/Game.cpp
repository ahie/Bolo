#include "Game.h"
#include "UI.h"
#include "Level.h"
#include "Terrain.h"
#include "Monster.h"
#include "HeroDeath.h"
#include "Inventory.h"
#include "UIButton.h"
#include "UIFunctions.h"
#include "Hero.h"
#include "LevelLoader.h"
#include "LevelEvent.h"
#include "VictoryMessage.h"
#include "HUD.h"

#include <string>
#include <unordered_map>
#include <set>

Game::Game() : gameRunning_(false), activeUI_(nullptr), activeLevel_(nullptr), activeHero_(nullptr) 
{
	UIFuncs::connect(this);
	UI* mainMenu = new UI();
	mainMenu->addElement(new UIButton(sf::Vector2i(210, 210), "NEW GAME", "diablo.ttf", 35, UIFuncs::newGame));
	mainMenu->addElement(new UIButton(sf::Vector2i(210, 270), "EXIT GAME", "diablo.ttf", 35, UIFuncs::exitGame));
	userInterfaces_.insert(std::make_pair("MAINMENU", mainMenu));
	setUI(mainMenu);
}

Game::~Game() { cleanUp(); }

void Game::cleanUp() { /* TODO: delete all objects here */ }

void Game::newGame() { initGame(); }

void Game::toggleOverlay()
{
	if (activeHero_ == nullptr) return; // Game not running
	UI* overlayUI = userInterfaces_.find("OVERLAYUI")->second; // if game running these exist
	UI* gameUI = userInterfaces_.find("GAMEUI")->second; // if game running these exist
	if (activeUI_ == gameUI)
		setUI(overlayUI);
	else if (activeUI_ == overlayUI)
		setUI(gameUI);
}

void Game::returnToMenu()
{
	deleteGameData();
	setUI(userInterfaces_.find("MAINMENU")->second);
}

void Game::enableGame()
{
	gameRunning_ = true;
}

void Game::disableGame()
{
	gameRunning_ = false;
}

void Game::update(float dt)
{
	if (activeLevel_ != nullptr && gameRunning_)
		activeLevel_->update(dt);
}

void Game::render(sf::RenderWindow& window)
{
	window.clear(sf::Color(0, 0, 0));
	if (activeHero_ != nullptr) {
		sf::View view;
		view.setSize(sf::Vector2f(640, 480));
		view.setCenter(activeHero_->getIsometricPos());
		window.setView(view);
	}
	if (activeLevel_ != nullptr)
		activeLevel_->render(window);
	if (activeUI_ != nullptr)
		activeUI_->render(window);
	window.display();
}

UI* Game::getUI() { return activeUI_; }

Hero* Game::getHero() { return activeHero_; }

void Game::initGame(string file)
{
	// Delete data of previous game
	deleteGameData();

	// Load playable game from file
	LevelLoader loader;
	loader.parseData(file);
	activeHero_ = loader.getHero();
	levels_ = loader.getLevels();

	activeLevel_ = levels_.at(loader.getHeroLevel());
	activeLevel_->addEntity(activeHero_);
	activeHero_->setLevel(activeLevel_);

	// GAME RELATED USER INTERFACES
	UI* overlayUI = new UI();
	UI* gameUI = new UI();
	userInterfaces_.insert(std::make_pair("OVERLAYUI", overlayUI));
	userInterfaces_.insert(std::make_pair("GAMEUI", gameUI));
	activeUI_ = gameUI;

	// OVERLAYUI
	overlayUI->addElement(new UIButton(sf::Vector2i(10, 10), "NEW GAME", "diablo.ttf", 35, UIFuncs::newGame));
	overlayUI->addElement(new UIButton(sf::Vector2i(10, 70), "EXIT GAME", "diablo.ttf", 35, UIFuncs::exitGame));

	// GAMEUI
	HUD* hud = new HUD(activeHero_);
	gameUI->addElement(hud);
	activeHero_->addObserver(hud);
	Inventory* inventory = new Inventory(activeHero_);
	gameUI->addElement(inventory);
	HeroDeath* heroDeath = new HeroDeath(this);
	gameUI->addElement(heroDeath);
	activeHero_->addObserver(heroDeath);
	VictoryMessage* victoryMessage = new VictoryMessage(this);
	gameUI->addElement(victoryMessage);

	// LEVEL EVENTS
	activeLevel_->addLevelEvent(new BossEvent(victoryMessage));

	// Start game
	enableGame();
}

void Game::deleteGameData() 
{ 
	activeUI_ = userInterfaces_.find("MAINMENU")->second; // guaranteed to exist
	activeHero_ = nullptr;
	activeLevel_ = nullptr;

	// delete all UIs except main menu
	unordered_map<string,UI*>::iterator iter = userInterfaces_.begin();
	while (iter != userInterfaces_.end()) {
		if (iter->first != "MAINMENU") {
			delete iter->second;
			userInterfaces_.erase(iter++);
		}
		else
			++iter;
	}

	// delete all levels (this also deletes the hero)
	for (auto level : levels_)
		delete level;
	levels_.clear();

	// delete all AIs
	for (auto ai : ais_)
		delete ai;
	ais_.clear();

	// delete all items
	for (auto item : items_)
		delete item;
	items_.clear();
}

void Game::setUI(UI* newUI) { activeUI_ = newUI; }

void Game::setLevel(Level* newLevel) { activeLevel_ = newLevel; }

void Game::setHero(Hero* hero) { activeHero_ = hero; }
