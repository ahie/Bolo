#pragma once
#include "Hero.h"
#include "UIElement.h"

#include <SFML\Window\Mouse.hpp>
#include <vector>

class Inventory : public UIElement
{
public:
	Inventory(sf::Sprite* sprite, Hero* hero);
	~Inventory();
	virtual void render(sf::RenderWindow& window);
	virtual bool handleInput(sf::Event event);
private:
	struct EquipmentContainer {
		EquipmentContainer(ItemSlot slot,
			sf::Vector2i oset,
			sf::Vector2i size);
		~EquipmentContainer();
		bool mouseOver(sf::Event event);

		ItemSlot slot;
		sf::Vector2i offset;
		sf::Vector2i size;
	};
	struct InventoryContainer {
		InventoryContainer(
			sf::Vector2i oset,
			sf::Vector2i size, 
			sf::Vector2i dimensions);
		~InventoryContainer();
		bool mouseOver(sf::Event event);
		int getX(sf::Event event);
		int getY(sf::Event event);

		sf::Vector2i dimensions;
		sf::Vector2i offset;
		sf::Vector2i size;
	};
	Hero* hero_;
	sf::Sprite* background_;
	std::vector<EquipmentContainer> equipmentContainers_;
	InventoryContainer inventoryContainer_;
};
