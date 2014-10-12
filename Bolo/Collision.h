#pragma once
#include "Terrain.h"
#include "Entity.h"
#include <vector>

class Collision
{
public:
	Collision() : 
		terrain_(nullptr) 
	{}
	~Collision() {}
	void setTerrain(Terrain* terrain) { terrain_ = terrain; }
	void addEntities(const std::vector<Entity*>& entity) { entities_ = entity; }
	bool checkCollision(sf::Vector2f at)
	{
		for (auto entity : entities_) {
			if (entity->checkCollision(at)) {
				return true;
			}
		}
		return terrain_->checkCollision(at);
	}
private:
	Terrain* terrain_;
	std::vector<Entity*> entities_;
};