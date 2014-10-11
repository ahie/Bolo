#pragma once

class Monster;

class MonsterAI
{
public:
	MonsterAI() {}
	~MonsterAI() {}
	virtual void think(Monster* who);
};