#include "Bonus.h"

void Bonus::Update() {
	if (Collide(&game.GetPlatform(), this)) {
		Destroy();
		Activate();
		return;
	}
	if (((float)game.GetWindow().getSize().y < Bottom())) {
		Destroy();
	}
	Move();
}

void Bonus::Draw() {
	game.GetWindow().draw(shape);
}

void Bonus::Destroy() {
	destroyed = true;
}

bool Bonus::IsDestroyed() {
	return destroyed;
}

void Bonus::Move() {
	shape.move(speed);
}

void MovingBrickBonus::Activate() {
	game.SpawnMovingBrick();
}