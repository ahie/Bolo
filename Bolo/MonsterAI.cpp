#include "MonsterAI.h"
#include "Monster.h"

MonsterAI::MonsterAI() {}
MonsterAI::~MonsterAI() {}
void MonsterAI::think(Monster* who)
{
	who->attack(sf::Vector2f(0.f, -1.f));
}