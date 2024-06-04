#pragma once

#include "global.h"
#include "Collider.h"
#include "GameObject.h"
#include "MovingObject.h"
#include "Platform.h"


class Bonus : public BoxCollider {
public:
	Bonus(Game& game, const sf::Vector2f& position, sf::Color color) : BoxCollider(game, shape) {
		shape.setSize({ Global::BonusWidth, Global::BonusHeight });
		shape.setPosition(position);
		shape.setFillColor(color);
		SetSpeed({ 0, Global::BonusFallingSpeed });
	}

	virtual void Activate() = 0;

	void Update() override;
	void Move() override;
	void Draw() override;

	void Destroy();
	bool IsDestroyed();


private:
	sf::RectangleShape shape;
	bool destroyed{ false };
};

class MovingBrickBonus : public Bonus {
public:
	MovingBrickBonus(Game& game, const sf::Vector2f& position) : Bonus(game, position, sf::Color::Green) {}

	virtual void Activate() override;
};