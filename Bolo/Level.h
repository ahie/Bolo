#pragma once
#include "Entity.h"
#include "Terrain.h"
#include "Attack.h"

#include <vector>

class Level : public Renderable
{
public:
	Level(): terrain_(nullptr) {}
	~Level() {}
	void setTerrain(Terrain* terrain) { terrain_ = terrain; }
	void setEntities(const std::vector<Entity*>& entities) { entities_ = entities; }
	void addEntity(Entity* entity) { entities_.push_back(entity); }
	void addAttack(Attack* attack)
	{
		Missile* missile = dynamic_cast<Missile*>(attack);
		if (missile) {
			missiles_.push_back(missile);
		}
		else {
			attacks_.push_back(attack);
		}
	}
	NavGraph* getNavGraph()
	{
		return terrain_->getNavGraph();
	}
	bool checkMissileCollision(Missile* missile)
	{
		for (auto entity : entities_) {
			if (missile->belongsTo() != entity->faction()) {
				if (entity->checkCollision(missile->getPos(), missile->getRadius())) {
					return true;
				}
			}
		}
		return terrain_->checkCollision(missile->getPos());
	}
	void update(float dt)
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
		for (auto missile : missiles_) {
			missile->advance(dt);
			if (checkMissileCollision(missile)) {
				attacks_.push_back(missile);
			}
		}
		for (auto attack : attacks_) {
			// Erase missiles that have collided
			missiles_.erase(find(missiles_.begin(),missiles_.end(),attack));
			for (auto entity : entities_) {
				if (attack->belongsTo() != entity->faction()) {
					if (entity->checkCollision(attack->getPos(), attack->getRadius())) {
						entity->damage(attack);
						if (attack->getType() == SINGLE_TARGET)
							break;
					}
				}
			}
			delete attack;
		}
		attacks_.clear();
	}
	void render(sf::RenderWindow& window)
	{
		terrain_->render(window);
		for (auto entity : entities_) entity->render(window);
		for (auto missile : missiles_) missile->render(window);
	}

private:
	Terrain* terrain_;
	std::vector<Entity*> entities_;
	std::vector<Attack*> attacks_;
	std::vector<Missile*> missiles_;
};