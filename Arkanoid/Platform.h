#pragma once

#include <SFML/Graphics.hpp>

#include "global.h"
#include "Collider.h"
#include "MovingObject.h"

class Platform : public BoxCollider {
public:
    Platform(Game& game, const sf::Vector2f& position) : BoxCollider(game, shape) {
        shape.setSize({ Global::PlatformWidth, Global::PlatformHeight });
        shape.setPosition(position);
    }

    virtual void Update() override;
    virtual void Move() override;
    virtual void Draw() override;

    void SetSize(const sf::Vector2f& size);
    sf::Vector2f GetSize();

private:
    sf::RectangleShape shape;
};