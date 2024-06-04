#pragma once

#include "global.h"
#include "Collider.h"
#include "MovingObject.h"
#include "Platform.h"
#include "Brick.h"

class Ball : public CircleCollider {

public:
    Ball(Game& game, const sf::Vector2f& position) : CircleCollider(game, shape) {
        SetSpeed({ Global::BallSpeedX, -Global::BallSpeedY });
        shape.setRadius(Global::BallRadius);
        shape.setPosition(position);
    }

    virtual void Update() override;
    virtual void Move() override;
    virtual void Draw() override;

private:
    sf::CircleShape shape;
};