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
	hp -= 1;
	if(IsDestroyed())
		game.IncreaseScore();
}

bool IndestructibleBrick::IsDestructible() {
	return false;
}

void IndestructibleBrick::Destroy() {}

void BonusBrick::Destroy() {

	Brick::Destroy();

	if (Brick::IsDestroyed()) {
		game.SpawnBonus(shape.getPosition());
	}
}


void MovingBrick::Move() {
	shape.move(speed);
}

void MovingBrick::Update() {

	if ((Left() < 0) || ((float)game.GetWindow().getSize().x < Right())) {
		RotateX();
	}
	bool handleX = true;
	bool handleY = true;

	for (auto& brick : game.GetBricks()) {
		if (brick->IsDestroyed()) {
			continue;
		}

		if (int orient = Collide(this, brick.get())) {

			if (handleX && orient > 0) {
				RotateX();
				handleX = false;
			}

		}
	}
	Move();
}

void AccelerationBrick::Destroy() {
	
	Brick::Destroy();
	if(IsDestroyed())
		game.Speedup();
}
