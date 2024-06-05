#pragma once

#include <SFML/Graphics.hpp>

#include "Game.h"

class GameObject {
public:
	virtual void Update() = 0;
	virtual void Draw() = 0;

protected:
	GameObject(Game& game) : game(game) {}

protected:
	Game& game;
};