#pragma once
#include "Terrain.h"
#include "Entity.h"
#include "Attack.h"

#include <vector>

class Level : public Renderable
{
public:
	Level(): terrain_(nullptr) {}
	~Level() {}
	void setTerrain(Terrain* terrain) { terrain_ = terrain; }
	void addEntities(const std::vector<Entity*>& entity) { entities_ = entity; }
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
			if (entity->checkCollision(missile->getPos(), missile->getRadius())) {
				return true;
			}
		}
		return terrain_->checkCollision(missile->getPos());
	}
	void update(float dt)
	{
		for (auto entity : entities_) entity->update(dt);
		for (auto missile : missiles_) {
			missile->advance(dt);
			if (checkMissileCollision(missile))
				attacks_.push_back(missile);
		}
		for (auto attack : attacks_) {
			// Erase missiles that have collided
			missiles_.erase(find(missiles_.begin(),missiles_.end(),attack));
			for (auto entity : entities_) {
				if (entity->checkCollision(attack->getPos(), attack->getRadius())) {
					entity->damage(attack);
					if (attack->getType() == SINGLE_TARGET)
						break;
				}
			}
			delete attack;
		}
		attacks_.clear();
	}
	void render(sf::RenderWindow& window)
	{
		for (auto entity : entities_) entity->render(window);
		for (auto missile : missiles_) missile->render(window);
	}

private:
	Terrain* terrain_;
	std::vector<Entity*> entities_;
	std::vector<Attack*> attacks_;
	std::vector<Missile*> missiles_;
};