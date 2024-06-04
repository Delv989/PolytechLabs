#pragma once
#include "GameObject.h"


class MovingObject : public GameObject {
protected:
    MovingObject(Game& game) : GameObject(game) {}

    void SetSpeed(const sf::Vector2f& speed);
    const sf::Vector2f& GetSpeed() const;

    virtual void Move() = 0;
    void RotateX();
    void RotateY();

protected:
    sf::Vector2f speed;
};