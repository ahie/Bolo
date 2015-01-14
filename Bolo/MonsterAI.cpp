#include "MonsterAI.h"
#include "Monster.h"

MonsterAI::MonsterAI() {}

MonsterAI::~MonsterAI() {}

void MonsterAI::think(Monster* who)
{
	float randomAngle = rand();
	float randomDistance = rand() % 100;
	sf::Vector2f clickPos = who->getPos() +
		sf::Vector2f(sin(randomAngle)*randomDistance, cos(randomAngle)*randomDistance);
	if (rand() % 50 < 1)
		who->handleInput(EntityEvent(true, EntityEvent::Click::RIGHT, clickPos));
	else if (rand() % 100 < 1)
		who->handleInput(EntityEvent(true, EntityEvent::Click::LEFT, clickPos));
}

DiabloAI::DiabloAI() {}

DiabloAI::~DiabloAI() {}

void DiabloAI::think(Monster* who)
{
	float randomAngle = rand();
	float randomDistance = rand() % 100;
	sf::Vector2f clickPos = who->getPos() + 
		sf::Vector2f(sin(randomAngle)*randomDistance, cos(randomAngle)*randomDistance);
	if (rand() % 20 < 1)
		who->handleInput(EntityEvent(true, EntityEvent::Click::RIGHT, clickPos));
	if (rand() % 5 < 1)
		who->castSpell(clickPos);
}