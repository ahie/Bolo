#include "Hero.h"

Hero::Hero() : 
	helmet_(nullptr), 
	weapon_(nullptr) 
{
	faction_ = FRIEND;
	for (int i = 0; i < INVENTORY_WIDTH; i++) {
		for (int j = 0; j < INVENTORY_HEIGHT; j++) {
			inventory_[i][j] = nullptr;
		}
	}
	//ANIM TESTING
	sf::Image* herowalk = new sf::Image();
	sf::Image* herostand = new sf::Image();
	sf::Image* heroattack = new sf::Image();
	herowalk->loadFromFile("Resources/Spritesheets/Hero/walk.png");
	herostand->loadFromFile("Resources/Spritesheets/Hero/stand.png");
	heroattack->loadFromFile("Resources/Spritesheets/Hero/attack.png");
	herowalk->createMaskFromColor(sf::Color(0, 0, 0), 0);
	herostand->createMaskFromColor(sf::Color(0, 0, 0), 0);
	heroattack->createMaskFromColor(sf::Color(0, 0, 0), 0);
	standAnimation_ =new Animation(96, herostand);
	walkAnimation_ =new Animation(96, herowalk);
	attackAnimation_ =new Animation(128, heroattack);
	state_->enter(*this);
}

Hero::~Hero() {}

void Hero::kill()
{
	notify(HERO_DIED);
}

void Hero::equip(ItemSlot slot)
{
	Item** item = pointerToSlot(slot);
	if (cursorItem_ == nullptr) {
		unequip(*item);
		cursorItem_ = *item;
		*item = nullptr;
		return;
	}
	if (cursorItem_->getSlot() == slot) {
		unequip(*item);
		// TODO: equip modifiers
		Item* placeholder = *item;
		*item = cursorItem_;
		cursorItem_ = placeholder;
	}
}

void Hero::inventoryClick(int x, int y)
{
	if (cursorItem_ == nullptr && inventory_[x][y] == nullptr)
		return;
	if (cursorItem_ == nullptr) {
		// Pick up item and clear pointers.
		cursorItem_ = inventory_[x][y];
		int clearWidth = inventory_[x][y]->getWidth();
		int clearHeight = inventory_[x][y]->getHeight();
		while (inventory_[x - 1][y] == cursorItem_)
			x -= 1;
		while (inventory_[x][y - 1] == cursorItem_)
			y -= 1;
		for (int i = x; i < x + clearWidth; i++) {
			for (int j = y; j < y + clearHeight; j++)
				inventory_[i][j] = nullptr;
		}
		return;
	}
	// Attempt to add item.
	if (addItem(cursorItem_, x, y))
		cursorItem_ = nullptr;
}

bool Hero::loot(Item* item)
{
	for (int i = 0; i < INVENTORY_WIDTH; i++) {
		for (int j = 0; j < INVENTORY_HEIGHT; j++) {
			if (addItem(item, i, j)) {
				return true;
			}
		}
	}
	notify(INVENTORY_FULL);
	return false;
}

bool Hero::addItem(Item* item, int x, int y)
{
	int itemWidth = item->getWidth();
	int itemHeight = item->getHeight();
	if (x + itemWidth > INVENTORY_WIDTH || y + itemHeight > INVENTORY_HEIGHT)
		return false;
	for (int i = x; i < x + itemWidth; i++) {
		for (int j = y; j < y + itemHeight; j++) {
			if (inventory_[i][j] != nullptr) return false;
		}
	}
	for (int i = x; i < x + itemWidth; i++) {
		for (int j = y; j < y + itemHeight; j++)
			inventory_[i][j] = item;
	}
	return true;
}

void Hero::unequip(Item* item)
{
	// TODO: reverse modifiers
}

sf::Sprite* Hero::getUISprite(ItemSlot slot)
{
	Item** slotPtr = pointerToSlot(slot);
	if (*slotPtr != nullptr)
		return (*slotPtr)->getUISprite();
	return nullptr;
}

std::vector<InventorySprite> Hero::getInventorySprites()
{
	std::vector<InventorySprite> sprites;
	std::vector<Item*> processed;
	for (int i = 0; i < INVENTORY_WIDTH; i++) {
		for (int j = 0; j < INVENTORY_HEIGHT; j++) {
			if (inventory_[i][j] != nullptr &&
				find(processed.begin(),processed.end(), inventory_[i][j]) == processed.end()) 
			{
				sprites.push_back(InventorySprite(inventory_[i][j]->getUISprite(), sf::Vector2i(i, j)));
				processed.push_back(inventory_[i][j]);
			}
		}
	}
	return sprites;
}

sf::Sprite* Hero::getCursorSprite()
{
	if (cursorItem_ != nullptr)
		return cursorItem_->getUISprite();
	return nullptr;
}

Item** Hero::pointerToSlot(ItemSlot slot)
{
	Item** slotPtr = nullptr;
	switch (slot)
	{
	case HELMET:
		slotPtr = &helmet_;
		break;
	case WEAPON:
		slotPtr = &weapon_;
		break;
	default:
		break;
	}
	return slotPtr;
}
