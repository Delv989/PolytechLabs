#pragma once

#include "global.h"
#include "Game.h"
#include "MovingObject.h"
#include <SFML/Graphics.hpp>

class Collider : public MovingObject {
protected:
    Collider(Game& game) : MovingObject(game) {}

    virtual float x() = 0;
    virtual float y() = 0;

public:
    virtual float Left() = 0;
    virtual float Right() = 0;
    virtual float Top() = 0;
    virtual float Bottom() = 0;
};

class BoxCollider : public Collider {
public:
    BoxCollider(Game& game, sf::RectangleShape& shape) : rect(shape), Collider(game) {}

protected:
    virtual float x() override;
    virtual float y() override;

public:
    virtual float Left() override;
    virtual float Right() override;
    virtual float Top() override;
    virtual float Bottom() override;

private:
    sf::RectangleShape& rect;
};

class CircleCollider : public Collider {
public:
    CircleCollider(Game& game, sf::CircleShape& shape) : circle(shape), Collider(game) {}

protected:
    virtual float x() override;
    virtual float y() override;

public:
    virtual float Left() override;
    virtual float Right() override;
    virtual float Top() override;
    virtual float Bottom() override;

private:
    sf::CircleShape& circle;
};

int Collide(Collider*, Collider*);

