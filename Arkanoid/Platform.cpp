#include "Platform.h"

void Platform::Update() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && Left() > 0) {
        SetSpeed({ -Global::PlatformSpeed, 0 });
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && Right() < game.GetWindow().getSize().x) {
        SetSpeed({ Global::PlatformSpeed, 0 });
    }
    else {
        SetSpeed({ 0, 0 });
    }
    Move();
}

void Platform::Move() {
    shape.move(speed);
}

void Platform::Draw() {
    game.GetWindow().draw(shape);
}

void Platform::SetSize(const sf::Vector2f& size) {
    shape.setSize(size);
}

sf::Vector2f Platform::GetSize() {
    return shape.getSize();
}