#pragma once
#include "gems.h"
#include "board.h"
#include <random>

class Bonus {
public:
	
	float bonusChance = 0.05;
	int const radius = 3;
	int i, j;
	std::random_device dev;
	std::mt19937 rndgen;

	virtual void activate(Board* board) {};
	Bonus() : rndgen(dev()) {};
};

class Bomb : public Bonus {
public:
	virtual void activate(Board* board);
	Bomb(int ni, int nj) {
		i = ni;
		j = nj;
	}

};

class Recolor : public Bonus {
public:
	ESprite color;
	virtual void activate(Board* board);
	Recolor(int ni, int nj, ESprite n_color) {
		i = ni; j = nj; color = n_color;
	}
};