#pragma once

class Monster;

class MonsterAI
{
public:
	MonsterAI();
	virtual ~MonsterAI();
	virtual void think(Monster* who);
};