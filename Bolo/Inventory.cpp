#include "Inventory.h"

Inventory::Inventory(Hero* hero) :
	UIElement(false, false), hero_(hero),
	inventoryContainer_(InventoryContainer(sf::Vector2i(338, 223), sf::Vector2i(290, 120), sf::Vector2i(29, 29)))
{
	texture_.loadFromFile("Resources/UI/Inventory.bmp");
	background_.setTexture(texture_);

	// Set clickable areas and actions.
	equipmentContainers_.push_back(EquipmentContainer(HELMET, sf::Vector2i(454, 4), sf::Vector2i(60, 60)));
	equipmentContainers_.push_back(EquipmentContainer(WEAPON, sf::Vector2i(338, 76), sf::Vector2i(57, 85)));
	equipmentContainers_.push_back(EquipmentContainer(CHEST_ARMOR, sf::Vector2i(452, 76), sf::Vector2i(57, 85)));
	// TODO: add all item slots
	//equipmentContainers_.push_back(EquipmentContainer(RING, sf::Vector2i(offset...), sf::Vector2i(offset...)));
	//...
}

Inventory::~Inventory() {}

void Inventory::render(sf::RenderWindow& window) {
	if (visible_) {

		// Render backdrop
		background_.setPosition(window.mapPixelToCoords(sf::Vector2i(320, 0)));
		window.draw(background_);

		// Render items in each equipment slot
		for (auto container : equipmentContainers_) {
			sf::Sprite* sprite = hero_->getUISprite(container.slot);
			if (sprite != nullptr) {
				(*sprite).setPosition(window.mapPixelToCoords(container.offset));
				window.draw(*sprite);
			}
		}

		// Render items in the inventory
		std::vector<InventorySprite> iSprites = hero_->getInventorySprites();
		for (auto iSprite : iSprites) {
			(*iSprite.first).setPosition(window.mapPixelToCoords(sf::Vector2i(
				iSprite.second.x*inventoryContainer_.dimensions.x + inventoryContainer_.offset.x,
				iSprite.second.y*inventoryContainer_.dimensions.y + inventoryContainer_.offset.y)));
			window.draw(*(iSprite.first));
		}
	}

	// If there's an item on the cursor, render it.
	sf::Sprite* cursorSprite = hero_->getCursorSprite();
	if (cursorSprite != nullptr) {
		(*cursorSprite).setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
		window.draw(*cursorSprite);
	}
}

bool Inventory::handleInput(sf::Event event)
{
	// Toggle inventory
	if (event.type == sf::Event::KeyPressed &&
		event.key.code == sf::Keyboard::I) {
		visible_ = !visible_;
		clickable_ = !clickable_;
		return true;
	}

	if (!clickable_) return false;

	// Route click to the right action
	if (event.type == sf::Event::MouseButtonPressed &&
		event.mouseButton.button == sf::Mouse::Left) {
		for (auto container : equipmentContainers_) {
			if (container.mouseOver(event)) {
				hero_->equip(container.slot);
				return true;
			}
		}
		if (inventoryContainer_.mouseOver(event)) {
			hero_->inventoryClick(inventoryContainer_.getX(event),
				inventoryContainer_.getY(event));
			return true;
		}
	}
	return false;
}

Inventory::EquipmentContainer::EquipmentContainer(
	ItemSlot slot,
	sf::Vector2i oset,
	sf::Vector2i size) :
		slot(slot),
		offset(oset),
		size(size) {}

Inventory::EquipmentContainer::~EquipmentContainer() {}

bool Inventory::EquipmentContainer::mouseOver(sf::Event event)
{
	float x = event.mouseButton.x;
	float y = event.mouseButton.y;
	return (x >= offset.x && x <= offset.x + size.x)
		&& (y >= offset.y && y <= offset.y + size.y);
}

Inventory::InventoryContainer::InventoryContainer(
	sf::Vector2i oset,
	sf::Vector2i size, 
	sf::Vector2i dimensions) :
		offset(oset), 
		size(size), 
		dimensions(dimensions) {}

Inventory::InventoryContainer::~InventoryContainer() {}

bool Inventory::InventoryContainer::mouseOver(sf::Event event)
{
	float x = event.mouseButton.x;
	float y = event.mouseButton.y;
	return (x >= offset.x && x <= offset.x + size.x)
		&& (y >= offset.y && y <= offset.y + size.y);
}

int Inventory::InventoryContainer::getX(sf::Event event) 
{ 
	return (event.mouseButton.x - offset.x) / dimensions.x; 
}

int Inventory::InventoryContainer::getY(sf::Event event) 
{
	return (event.mouseButton.y - offset.y) / dimensions.y; 
}
