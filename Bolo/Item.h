#pragma once

enum ItemSlot { HELMET, WEAPON, RING, AMULET, SECOND_RING, CHEST_ARMOR, OFFHAND };

class Item
{
public:
	Item(sf::Sprite* uiSprite, ItemSlot slot, int width, int height) :
		uiSprite_(uiSprite), slot_(slot), width_(width), height_(height) {}
	virtual ~Item() {}
	sf::Sprite* getUISprite() { return uiSprite_; }
	ItemSlot getSlot() { return slot_; }
	int getWidth() { return width_; }
	int getHeight() { return height_; }
private:
	int width_;
	int height_;
	ItemSlot slot_;
	sf::Sprite* uiSprite_;
};