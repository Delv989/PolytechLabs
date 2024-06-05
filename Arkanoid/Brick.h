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

class AccelerationBrick : public Brick {
public:
    AccelerationBrick(Game& game, const sf::Vector2f& position) : Brick(game, position) {
        shape.setFillColor(fillColor);
    }

    virtual void Destroy() override;

private:
    sf::Color fillColor{ sf::Color::Blue };
};

class BonusBrick : public Brick {
public:
    BonusBrick(Game& game, const sf::Vector2f& position) : Brick(game, position) {
        shape.setFillColor(fillColor);
    }

    virtual void Destroy() override;

private:
    sf::Color fillColor{ sf::Color::Yellow };
};

class MovingBrick : public Brick {
public:
    MovingBrick(Game& game) : Brick(game, sf::Vector2f{ Global::WindowWidth / 2.f, Global::WindowHeight * 0.75f }) {
        shape.setFillColor(fillColor);
        SetSpeed({ Global::BallSpeedX, 0 });
        hp = 3;
    }
    

    virtual void Move() override;
    virtual void Update() override;

private:
    sf::Color fillColor{ sf::Color::White };
    int hp;
};