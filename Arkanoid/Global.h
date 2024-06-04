#pragma once
namespace Global {


    static constexpr unsigned int WindowHeight = 800;
    static constexpr unsigned int WindowWidth = 600;

    static constexpr int IterationsPerFrame = 16;

    static constexpr float PlatformSpeed = .5f;
    static constexpr float PlatformWidth = 80.f;
    static constexpr float PlatformHeight = 12.f;

    static constexpr float BallRadius = 10.f;
    static constexpr int BallAcceleration = 4;
    static constexpr float BallSpeedX = .3f;
    static constexpr float BallSpeedY = .4f;

    static constexpr int BricksCountX = 8;
    static constexpr int BricksCountY = 10;
    static constexpr int BricksGap = 5;

    static constexpr int BrickWidth = (WindowWidth - BricksGap) / BricksCountX - BricksGap;
    static constexpr int BrickHeight = (WindowHeight - BricksGap) / BricksCountY / 2 - BricksGap;

    static constexpr float BonusWidth = BrickWidth / 2.f;
    static constexpr float BonusHeight = BrickHeight / 2.f;
    static constexpr float BonusFallingSpeed = .15f;
}