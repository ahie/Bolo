#pragma once
#include "LevelEventInterface.h"
#include "Diablo.h" // BossEvent
#include "Observer.h" // BossEvent

class LevelEvent
{
public:
	LevelEvent() {}
	virtual ~LevelEvent() {}
	virtual void checkTrigger(LevelEventInterface* interface) = 0;
};

class BossEvent : public LevelEvent
{
public:
	BossEvent(Observer* victoryMessage) : 
		victoryMessage_(victoryMessage),
		triggered_(false) {}
	virtual void checkTrigger(LevelEventInterface* interface)
	{
		if (interface->getMonsterCount() == 0 && !triggered_){
			Entity* endBoss = new Diablo();
			endBoss->setLevel(interface->getPointerToLevel());
			endBoss->setPosition(sf::Vector2f(400,400));
			endBoss->addObserver(victoryMessage_);
			interface->spawnEntity(endBoss);
			triggered_ = true;
		}
	}
private:
	Observer* victoryMessage_;
	bool triggered_;
};