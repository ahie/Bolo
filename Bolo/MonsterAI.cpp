#include "MonsterAI.h"
#include "Monster.h"

MonsterAI::MonsterAI() {}
MonsterAI::~MonsterAI() {}
void MonsterAI::think(Monster* who)
{
	sf::Vector2f clickPos(rand() % 10000 - 5000, rand() % 10000 - 5000);
	if (rand() % 1000 < 1)
	{
		who->handleInput(EntityEvent(true, EntityEvent::Click::RIGHT, clickPos));
	}
	else if (rand() % 10000 < 1)
	{
		who->handleInput(EntityEvent(true, EntityEvent::Click::LEFT, clickPos));
	}
}