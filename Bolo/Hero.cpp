#include "Hero.h"
#include "Level.h"
#include "DeathState.h"
#include "TextureContainer.h"

Hero::Hero() : Entity("Hero", FRIEND, AttackDescriptor(50.0f, 10.0f, 2.0f, MISSILE, SINGLE_TARGET, PURE, "Arrow.png")),
	cursorItem_(nullptr),
	chestArmor_(nullptr),
	helmet_(nullptr), 
	weapon_(nullptr)
{
	for (int i = 0; i < INVENTORY_WIDTH; i++) {
		for (int j = 0; j < INVENTORY_HEIGHT; j++) {
			inventory_[i][j] = nullptr;
		}
	}
	addAnimation(STAND, new Animation(96, TextureContainer::instance().getTexture("Resources/Spritesheets/Hero/stand.png")));
	addAnimation(WALK, new Animation(96, TextureContainer::instance().getTexture("Resources/Spritesheets/Hero/walk.png")));
	addAnimation(ATTACK, new Animation(128, TextureContainer::instance().getTexture("Resources/Spritesheets/Hero/attack.png")));
	addAnimation(DEATH, new Animation(96, TextureContainer::instance().getTexture("Resources/Spritesheets/Hero/stand.png")));
	getState()->enter(*this);
}

Hero::~Hero() 
{
	// delete items owned by hero
	delete cursorItem_;
	cursorItem_ = nullptr;
	for (int i = 0; i < INVENTORY_WIDTH; i++) {
		for (int j = 0; j < INVENTORY_HEIGHT; j++) {
			// =D
			inventoryClick(i, j);
			delete cursorItem_;
			cursorItem_ = nullptr;
		}
	}
	delete chestArmor_;
	delete helmet_;
	delete weapon_;
}

void Hero::kill()
{
	notify(HERO_DIED);
}

void Hero::handleInput(EntityEvent event)
{
	if (event.clickType == EntityEvent::Click::LEFT &&
		cursorItem_ != nullptr) {
		getLevel()->dropItem(cursorItem_, getPos());
		cursorItem_ = nullptr;
		return;
	}
	if (event.clickType == EntityEvent::Click::LEFT &&
		getLevel()->attemptLoot(this, getPos())) {
		return;
	}
	Entity::handleInput(event);
}

void Hero::applyItemModifiers(const StatModifiers& mods)
{
	for (auto mod : mods) {
		applyModifier(mod);
	}
	notify(HERO_STAT_CHANGE);
}

void Hero::equip(ItemSlot slot)
{
	Item** item = pointerToSlot(slot);
	if (cursorItem_ == nullptr) {
		if (*item != nullptr)
			unequip((*item)->getStatModifiers());
		cursorItem_ = *item;
		*item = nullptr;
		return;
	}
	if (cursorItem_->getSlot() == slot) {
		if (*item != nullptr)
			unequip((*item)->getStatModifiers());
		applyItemModifiers(cursorItem_->getStatModifiers());
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

void Hero::unequip(StatModifiers mods)
{
	for (auto mod : mods) {
		mod.second = -mod.second;
		applyModifier(mod);
	}
	notify(HERO_STAT_CHANGE);
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
	case CHEST_ARMOR:
		slotPtr = &chestArmor_;
		break;
	default:
		break;
	}
	return slotPtr;
}
