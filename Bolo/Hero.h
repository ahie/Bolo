#pragma once
#include "Entity.h"
#include "Item.h"

#include <list>

typedef std::pair<sf::Sprite*, sf::Vector2i> InventorySprite;

const int INVENTORY_WIDTH = 10;
const int INVENTORY_HEIGHT = 4;

class Hero: public Entity
{
public:
	Hero();
	~Hero();
	bool loot(Item* item);
	sf::Sprite* getUISprite(ItemSlot slot);
	sf::Sprite* getCursorSprite();
	std::vector<InventorySprite> getInventorySprites();
	void equip(ItemSlot slot);
	void inventoryClick(int x, int y);
private:
	void kill();
	bool addItem(Item* item, int x, int y);
	void unequip(Item* item);
	Item** pointerToSlot(ItemSlot slot);

	Item* inventory_[INVENTORY_WIDTH][INVENTORY_HEIGHT];
	Item* cursorItem_;
	Item* weapon_;
	Item* helmet_;
};
