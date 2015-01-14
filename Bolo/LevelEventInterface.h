#pragma once

class Entity;
class Level;
class LevelEvent;

class LevelEventInterface
{
public:
	LevelEventInterface() {}
	virtual ~LevelEventInterface() {}
	virtual int getMonsterCount() = 0;
	virtual void spawnEntity(Entity* e) = 0;
	virtual void addLevelEvent(LevelEvent* e) = 0;
	virtual Level* getPointerToLevel() = 0;
};