#include "Item.h"

static sf::Vector2f cartesianToIso(sf::Vector2f point)
{
	return sf::Vector2f(point.x - point.y, (point.x + point.y) / 2.0f);
}

ItemDescriptor::ItemDescriptor(std::string n,
	ItemSlot s,
	int w, int h,
	StatModifiers m,
	std::string uii, std::string gi) :
		name(n), slot(s),
		inventoryHeight(h),
		inventoryWidth(w),
		mods(m),
		uiImage(uii), groundImage(gi) {}

Item::Item(ItemDescriptor item) :
	slot_(item.slot),
	width_(item.inventoryWidth),
	height_(item.inventoryHeight),
	name_(item.name),
	modifiers_(item.mods),
	groundPos_(sf::Vector2f())
{
	sf::Image uiImage;
	uiImage.loadFromFile("Resources/Items/UI/" + item.uiImage);
	uiImage.createMaskFromColor(sf::Color(0, 0, 0), 150);
	uiTexture_.loadFromImage(uiImage);
	uiSprite_.setTexture(uiTexture_);

	sf::Image groundImage;
	groundImage.loadFromFile("Resources/Items/Sprites/" + item.groundImage);
	groundImage.createMaskFromColor(sf::Color(0, 0, 0), 0);
	groundTexture_.loadFromImage(groundImage);
	groundSprite_.setTexture(groundTexture_);
}

Item::~Item() {}

sf::Sprite* Item::getUISprite() { return &uiSprite_; }

ItemSlot Item::getSlot() { return slot_; }

int Item::getWidth() { return width_; }

int Item::getHeight() { return height_; }

void Item::setGroundPos(sf::Vector2f pos) { groundPos_ = pos; }

StatModifiers Item::getStatModifiers() { return modifiers_; }

sf::Vector2f Item::getGroundPos() { return groundPos_; }

RenderableSprite Item::requestSprite()
{
	groundSprite_.setPosition(cartesianToIso(groundPos_) - sf::Vector2f(48, 160));
	return RenderableSprite(groundSprite_, groundPos_);
}

void Item::render(sf::RenderWindow& window) {}