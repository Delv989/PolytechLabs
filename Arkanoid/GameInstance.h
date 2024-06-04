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

    void Start();
    void Run();


private:
    void SpawnBricks();

private:
    sf::RenderWindow mWindow;

    Platform mPlatform;

    std::list<std::shared_ptr<Brick>> bricks;
    std::shared_ptr<Ball> ball;

    int score{ 0 };


    int fps{ Global::IterationsPerFrame };
};
