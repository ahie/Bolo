#include "Level.h"
#include "Entity.h"
#include "Terrain.h"
#include "Attack.h"
#include "Hero.h"
#include "Missile.h"
#include "LevelEvent.h"

#include <algorithm>

Level::Level() : terrain_(nullptr) {}

Level::~Level()
{
	delete terrain_;
	for (auto entity : entities_)
		delete entity;
	for (auto attack : attacks_)
		delete attack;
	for (auto missile : missiles_)
		delete missile;
	for (auto item : groundItems_)
		delete item;
	for (auto event : levelEvents_)
		delete event;
}

void Level::setTerrain(Terrain* terrain) { terrain_ = terrain; }

void Level::setEntities(const std::vector<Entity*>& entities) { entities_ = entities; }

void Level::addEntity(Entity* entity) { entities_.push_back(entity); }

void Level::addAttack(AttackDescriptor& aDescriptor, 
	Entity& source, sf::Vector2f& pos, sf::Vector2f& direction)
{
	switch (aDescriptor.atckClass) {
	case MELEE:
		attacks_.push_back(new Attack(aDescriptor, source.getFaction(), pos));
		break;
	case MISSILE:
		missiles_.push_back(new Missile(aDescriptor, source.getFaction(), pos, direction));
		break;
	default:
		break;
	}
}

NavGraph* Level::getNavGraph()
{
	return terrain_->getNavGraph();
}

bool Level::checkMissileCollision(Missile* missile)
{
	for (auto entity : entities_) {
		if (missile->belongsTo() != entity->getFaction()) {
			if (entity->checkCollision(missile->getPos(), missile->getRadius())) {
				return true;
			}
		}
	}
	return terrain_->checkCollision(missile->getPos());
}

void Level::update(float dt)
{
	// Remove dead monsters
	entities_.erase(std::remove_if(entities_.begin(), entities_.end(),
		[](Entity* e){
		if (!e->isAlive()) {
			delete e;
			return true;
		}
		return false;
	}), entities_.end());

	for (auto entity : entities_) entity->update(dt);

	handleAttacks(dt);

	for (auto levelEvent : levelEvents_) levelEvent->checkTrigger(this);
}

void Level::handleAttacks(float dt)
{
	for (auto missile : missiles_) {
		missile->advance(dt);
		if (checkMissileCollision(missile)) {
			attacks_.push_back(missile);
		}
	}
	for (auto attack : attacks_) {
		// Erase missiles that have collided
		std::vector<Missile*>::iterator mIter = find(missiles_.begin(), missiles_.end(), attack);
		if (mIter != missiles_.end()) missiles_.erase(mIter);

		for (auto entity : entities_) {
			if (attack->belongsTo() != entity->getFaction()) {
				if (entity->checkCollision(attack->getPos(), attack->getRadius())) {
					entity->damage(attack);
					if (attack->getType() == SINGLE_TARGET)
						break;
				}
			}
		}
	}
	for (auto attack : attacks_) delete attack;
	attacks_.clear();
}

void Level::spawnItem(sf::Vector2f pos)
{
	if (spawnableItems_.empty()) return;
	int index = rand() % spawnableItems_.size();
	Item* newItem = new Item(spawnableItems_.at(index));
	newItem->setGroundPos(pos);
	groundItems_.push_back(newItem);
}

void Level::addSpawnableItem(ItemDescriptor item)
{
	spawnableItems_.push_back(item);
}

void Level::dropItem(Item* item, sf::Vector2f pos)
{
	item->setGroundPos(pos);
	groundItems_.push_back(item);
}

bool Level::attemptLoot(Hero* hero, sf::Vector2f pos)
{
	std::vector<Item*>::iterator iter = groundItems_.begin();
	while (iter != groundItems_.end()) {
		sf::Vector2f gpos = (*iter)->getGroundPos();
		if (((gpos.x - pos.x)*(gpos.x - pos.x) + 
			(gpos.y - pos.y)*(gpos.y - pos.y)) < PICKUP_RADIUS * PICKUP_RADIUS)
			break;
		iter++;
	}
	if (iter != groundItems_.end()) {
		if(hero->loot(*iter))
			groundItems_.erase(iter);
		return true;
	}
	return false;
}

void Level::render(sf::RenderWindow& window)
{
	// Gather sprites
	std::vector<RenderableSprite> sprites;
	std::vector<RenderableSprite> terrainSprites = terrain_->requestSprites();
	sprites.insert(sprites.end(),terrainSprites.begin(),terrainSprites.end());
	for (auto entity : entities_) sprites.push_back(entity->requestSprite());
	for (auto missile : missiles_) sprites.push_back(missile->requestSprite());
	for (auto item : groundItems_) sprites.push_back(item->requestSprite());
	
	// Depth sort sprites
	std::sort(sprites.begin(), sprites.end());

	// Render
	for (auto renderable : sprites) window.draw(renderable.sprite);
}

int Level::getMonsterCount()
{
	return entities_.size() - 1; // Subtract hero.
}

void Level::spawnEntity(Entity* e)
{
	entities_.push_back(e);
}

void Level::addLevelEvent(LevelEvent* event)
{
	levelEvents_.push_back(event);
}

Level* Level::getPointerToLevel()
{
	return this;
}
