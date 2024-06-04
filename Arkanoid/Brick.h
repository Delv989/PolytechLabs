#pragma once

#include "Collider.h"
#include "GameObject.h"

#include <iostream>


class Brick : public BoxCollider {
public:
    virtual void Destroy();
    virtual bool IsDestroyed();
    virtual bool IsDestructible();

    virtual void Update() override;
    virtual void Move() override;
    virtual void Draw() override;

protected:
    Brick(Game& game, const sf::Vector2f& position) : BoxCollider(game, shape) {
        shape.setSize({ Global::BrickWidth, Global::BrickHeight });
        shape.setPosition(position);
        hp = 2;
    }
protected:
    sf::RectangleShape shape;
    int hp;
};

class DefaultBrick : public Brick{
    public:
        DefaultBrick(Game & game, const sf::Vector2f & position) : Brick(game, position) {
            shape.setFillColor(fillColor);
        }

    private:
        sf::Color fillColor{ sf::Color::Green };
};

class IndestructibleBrick : public Brick {
public:
    IndestructibleBrick(Game& game, const sf::Vector2f& position) : Brick(game, position) {
        shape.setFillColor(fillColor);
    }

    virtual bool IsDestructible() override;
    virtual void Destroy() override;

private:
    sf::Color fillColor{ sf::Color::Red };
};