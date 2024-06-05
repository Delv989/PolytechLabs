#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>

#include "Game.h"
#include "global.h"
#include "Collider.h"
#include "GameObject.h"
#include "Platform.h"
#include "Ball.h"
#include "Brick.h"
#include "Bonus.h"


class GameInstance : public Game {
public:
    GameInstance(const sf::Vector2f& platform_pos);

    virtual void IncreaseScore() override;
    virtual void DecreaseScore() override;

    virtual Platform& GetPlatform() override;
    virtual std::shared_ptr<Ball> GetBall() override;
    virtual std::list<std::shared_ptr<Brick>>& GetBricks() override;
    virtual sf::RenderWindow& GetWindow() override;
    virtual void SpawnBall() override;
    virtual void SpawnBonus(const sf::Vector2f& position) override;

    virtual void SpawnMovingBrick() override;

    virtual void MakeFloorPlatform() override;
    virtual bool isFloorPlatform() override;
    virtual void DeleteFloorPlatform() override;

    virtual void ExtendPlatform() override;

    void Start();
    void Run();

    virtual void Speedup() override;


   

private:
    void SpawnBricks();

private:
    sf::RenderWindow mWindow;

    Platform mPlatform;

    std::list<std::shared_ptr<Brick>> bricks;
    std::shared_ptr<Ball> ball;
    std::list<std::shared_ptr<Bonus>> bonuses;

    int score{ 0 };

    bool hasFloorPlatform{ false };

    int fps{ Global::IterationsPerFrame };
};
