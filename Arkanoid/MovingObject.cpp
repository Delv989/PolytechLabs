#include "MovingObject.h"

void MovingObject::SetSpeed(const sf::Vector2f& speed) {
	this->speed = speed;
}

const sf::Vector2f& MovingObject::GetSpeed() const {
	return speed;
}

void MovingObject::RotateX() {
	speed.x = -speed.x;
}

void MovingObject::RotateY() {
	speed.y = -speed.y;
}