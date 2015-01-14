#pragma once

#include "Renderable.h"

#include <string>
#include <map>

enum ItemSlot { HELMET, WEAPON, RING, AMULET, SECOND_RING, CHEST_ARMOR, OFFHAND };
enum ModType { ARMOR, HPREGEN, DAMAGE };
typedef std::map<ModType, float> StatModifiers;

struct ItemDescriptor
{
	std::string name;
	ItemSlot slot;
	int inventoryWidth;
	int inventoryHeight;
	StatModifiers mods;

	std::string uiImage;
	std::string groundImage;

	ItemDescriptor(std::string n,
		ItemSlot s,
		int w, int h,
		StatModifiers m,
		std::string uii, std::string gi);
};

// TODO: modifiers

class Item : public Renderable
{
public:
	Item(ItemDescriptor item);
	virtual ~Item();
	sf::Sprite* getUISprite();
	ItemSlot getSlot();
	int getWidth();
	int getHeight();
	void setGroundPos(sf::Vector2f pos);
	sf::Vector2f getGroundPos();
	virtual RenderableSprite requestSprite();
	virtual void render(sf::RenderWindow& window);
	StatModifiers getStatModifiers();
private:
	std::string name_;
	int width_;
	int height_;
	ItemSlot slot_;
	StatModifiers modifiers_;

	sf::Vector2f groundPos_;

	// UI graphics
	sf::Texture uiTexture_;
	sf::Sprite uiSprite_;

	// Ground graphics
	// TODO: drop animation
	sf::Texture groundTexture_;
	sf::Sprite groundSprite_;
};