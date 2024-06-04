#include "Ball.h"

void Ball::Update() {
    if ((Left() < 0) || ((float)game.GetWindow().getSize().x < Right())) {
        RotateX();
    }

    if (Top() < 0) {
        RotateY();
    }

    if ((float)game.GetWindow().getSize().y < Bottom()) {
        game.DecreaseScore();
        RotateY();
    }

    if (Collide(this, &game.GetPlatform()) < 0 && (Bottom() < game.GetPlatform().Bottom())) {
        RotateY();
    }

    bool handleX = true;
    bool handleY = true;

    for (auto& brick : game.GetBricks()) {
        if (brick->IsDestroyed()) {
            continue;
        }

        if (int orient = Collide(this, brick.get())) {
            brick->Destroy();
            if (handleX && orient > 0) {
                RotateX();
                handleX = false;
            }
            if (handleY && orient < 0) {
                RotateY();
                handleY = false;
            }
        }
    }

    Move();
}

void Ball::Move() {
    shape.move(speed);
}

void Ball::Draw() {
    game.GetWindow().draw(shape);
}