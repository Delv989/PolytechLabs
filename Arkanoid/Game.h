#pragma once

#include <list>

#include <SFML/Graphics.hpp>

class Platform;
class Ball;
class Brick;
class Bonus;

class Game {
public:
    virtual void IncreaseScore() = 0;

    virtual Platform& GetPlatform() = 0;
    virtual std::list<std::shared_ptr<Ball>>& GetBalls() = 0;
    virtual std::list<std::shared_ptr<Brick>>& GetBricks() = 0;
    virtual sf::RenderWindow& GetWindow() = 0;
    virtual void SpawnBall() = 0;
    virtual void SpawnBonus(const sf::Vector2f& position) = 0;


    virtual void SpawnHelpBrick() = 0;
    virtual void DestroyHelpBrick() = 0;

    virtual void Speedup() = 0;
};