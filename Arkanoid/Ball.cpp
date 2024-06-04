#include "Ball.h"

void Ball::Update() {
    if ((Left() < 0) || ((float)game.GetWindow().getSize().x < Right())) {
        RotateX();
    }

    if (Top() < 0) {
        RotateY();
    }

    if ((float)game.GetWindow().getSize().y < Bottom()) {
        alive = false;
        return;
    }

    if (Collide(this, &game.GetPlatform()) < 0 && (Bottom() < game.GetPlatform().Bottom())) {
        RotateY();
    }

    bool handleX = true;
    bool handleY = true;

    //написать проверку столкновени€ с кирпичами

    Move();
}

bool Ball::IsAlive() {
    return alive;
}

void Ball::Move() {
    shape.move(speed);
}

void Ball::Draw() {
    game.GetWindow().draw(shape);
}