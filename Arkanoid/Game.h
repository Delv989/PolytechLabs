#pragma once

#include <list>

#include <SFML/Graphics.hpp>

class Platform;
class Ball;
class Brick;

class Game {
public:
    virtual void IncreaseScore() = 0;
    virtual void DecreaseScore() = 0;

    virtual Platform& GetPlatform() = 0;
    virtual std::shared_ptr<Ball> GetBall() = 0;
    virtual std::list<std::shared_ptr<Brick>>& GetBricks() = 0;
    virtual sf::RenderWindow& GetWindow() = 0;
    virtual void SpawnBall() = 0;
    virtual void SpawnBonus(const sf::Vector2f& position) = 0;


    virtual void SpawnMovingBrick() = 0;

    virtual void MakeFloorPlatform() = 0;
    virtual bool isFloorPlatform() = 0;
    virtual void DeleteFloorPlatform() = 0;

    virtual void ExtendPlatform() = 0;
    

    virtual void Speedup() = 0;

};