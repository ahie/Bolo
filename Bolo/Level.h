#pragma once
#include "Renderable.h"
#include "LevelEventInterface.h"
#include "Item.h"
#include <vector>

struct AttackDescriptor;

class Entity;
class Hero;
class Terrain;
class Attack;
class Missile;
class NavGraph;
class LevelEvent;

const float PICKUP_RADIUS = 50.f;

// Level class: handles high level game logic of the currently active level.
// Enables entities to interact with each other(attacks), the terrain and items.

// TODO: handle attacks elsewhere?
// TODO: handle loot elsewhere?

class Level : public Renderable,
	public LevelEventInterface
{
public:
	Level();
	~Level();

	void setTerrain(Terrain* terrain);
	void setEntities(const std::vector<Entity*>& entities);
	void addEntity(Entity* entity);
	void addAttack(AttackDescriptor& aDescriptor, Entity& source, sf::Vector2f& pos, sf::Vector2f& direction);
	NavGraph* getNavGraph();
	void update(float dt);
	void render(sf::RenderWindow& window);

	void addSpawnableItem(ItemDescriptor item);
	void spawnItem(sf::Vector2f pos);
	void dropItem(Item* item, sf::Vector2f pos);
	bool attemptLoot(Hero* hero, sf::Vector2f pos);

	// LevelEventInterface
	virtual int getMonsterCount();
	virtual void spawnEntity(Entity* e);
	virtual void addLevelEvent(LevelEvent* e);
	virtual Level* getPointerToLevel();

private:
	bool checkMissileCollision(Missile* missile);
	void handleAttacks(float dt);

	std::vector<ItemDescriptor> spawnableItems_;
	std::vector<Item*> groundItems_;

	Terrain* terrain_;
	std::vector<Entity*> entities_;
	std::vector<Attack*> attacks_;
	std::vector<Missile*> missiles_;

	std::vector<LevelEvent*> levelEvents_;
};