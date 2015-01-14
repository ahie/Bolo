#pragma once

class Monster;

class MonsterAI
{
public:
	MonsterAI();
	virtual ~MonsterAI();
	virtual void think(Monster* who);
};

class DiabloAI : public MonsterAI
{
public:
	DiabloAI();
	virtual ~DiabloAI();
	virtual void think(Monster* who);
};