#pragma once
#include "Entity.h"
#include "Item.h"

#include <list>

typedef std::pair<sf::Sprite*, sf::Vector2i> InventorySprite;

const int INVENTORY_WIDTH = 10;
const int INVENTORY_HEIGHT = 4;

// Player controlled character.
// Has items, inventory and additional stats.
class Hero: public Entity
{

public:

	Hero();
	~Hero();
	bool loot(Item* item);
	sf::Sprite* getUISprite(ItemSlot slot);
	sf::Sprite* getCursorSprite();
	std::vector<InventorySprite> getInventorySprites();
	virtual void handleInput(EntityEvent event);
	void equip(ItemSlot slot);
	void inventoryClick(int x, int y);

private:
	void kill();
	bool addItem(Item* item, int x, int y);
	void unequip(StatModifiers mods);
	void applyItemModifiers(const StatModifiers& mods);

	// TODO: better logic for items...
	Item* inventory_[INVENTORY_WIDTH][INVENTORY_HEIGHT];
	Item* cursorItem_;

	Item** pointerToSlot(ItemSlot slot);
	Item* weapon_;
	Item* helmet_;
	Item* chestArmor_;

};
