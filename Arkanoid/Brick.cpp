#include "Brick.h"

bool Brick::IsDestroyed() {
	return !hp;
}

bool Brick::IsDestructible() {
	return true;
}

void Brick::Update() {}

void Brick::Draw() {
	game.GetWindow().draw(shape);
}

void Brick::Move() {}

void Brick::Destroy() {
	game.IncreaseScore();
	hp -= 1;
}

bool IndestructibleBrick::IsDestructible() {
	return false;
}

void IndestructibleBrick::Destroy() {}
