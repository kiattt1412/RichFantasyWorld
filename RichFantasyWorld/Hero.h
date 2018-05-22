#pragma once
#include <iostream>
#include "Map.h"
#include "Monster.h"
#include <vector>
#include <memory>
using namespace std;

class Hero
{
public:
	Hero();
	~Hero();
	double heroHP;
	int heroAtkDamage;
	int heroPositionX;
	int heroPositionY;
	int monfightID;
	bool isFighting;
	bool isAlive;
	void heroMove(char c, Map &m, vector<std::shared_ptr<Monster>> &monStore);
	void heroMoveOut(char c, Map &m, vector<std::shared_ptr<Monster>> &monStore);
	void setHeroPosition(int x, int y, Map &m);
	void heroAttack(vector<std::shared_ptr<Monster>> &monStore2, Map &m, int, int, int monposX, int monposY);
	void damageCal(vector<std::shared_ptr<Monster>> &monStore2, Map &m);
	Hero(const Hero& hr) = default;
	Hero& operator = (Hero& hr) = default;
};