#include "GameInstance.h"

GameInstance::GameInstance(const sf::Vector2f& platform_pos)
    : mWindow({ Global::WindowWidth, Global::WindowHeight }, "Arkanoid"),
    mPlatform(*this, platform_pos) {

    mWindow.setFramerateLimit(60);
}

void GameInstance::IncreaseScore() {
    score++;
}

void GameInstance::DecreaseScore() {
    score--;
}

void GameInstance::Start() {
    std::srand((unsigned int)std::time(NULL));

    SpawnBall();

    SpawnBricks();

    Run();

    mWindow.close();
}

void GameInstance::Run() {
    while (true) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
            std::cout << score;
            return;
        }

        for (int i = 0; i < fps; ++i) {
            mPlatform.Update();
            for (auto brick : bricks) {
                brick->Update();
            }
            for (auto bonus : bonuses) {
                bonus->Update();
            }
            ball->Update();


            bool win = true;
            auto it = bricks.begin();

            while (it != bricks.end()) {
                if ((*it)->IsDestroyed()) {
                    it = bricks.erase(it);
                    continue;
                }

                if (win && (*it)->IsDestructible()) {
                    win = false;
                }
                it++;
            }

            auto bonusesIter = bonuses.begin();
            while (bonusesIter != bonuses.end()) {
                if ((*bonusesIter)->IsDestroyed()) {
                    bonusesIter = bonuses.erase(bonusesIter);
                    continue;
                }
                bonusesIter++;
            }

            if (win) {
                std::cout << score;
                return;
            }
        }

        mWindow.clear(sf::Color::Black);
        mPlatform.Draw();

        ball->Draw();

        for (auto brick : bricks) {
            brick->Draw();
        }

        for (auto bonus : bonuses) {
            bonus->Draw();
        }

        mWindow.display();
    }
}

Platform& GameInstance::GetPlatform() {
    return mPlatform;
}

std::shared_ptr<Ball> GameInstance::GetBall() {
    return ball;
}

std::list<std::shared_ptr<Brick>>& GameInstance::GetBricks() {
    return bricks;
}

sf::RenderWindow& GameInstance::GetWindow() {
    return mWindow;
}

void GameInstance::SpawnBall() {
    ball = std::make_shared<Ball>(*this, sf::Vector2f{ Global::WindowWidth / 2.f, Global::WindowHeight * 2.f / 3.f });
}


void GameInstance::SpawnBricks() {
    int id = 0;
    for (int i = 0; i < Global::BricksCountY; ++i) {
        for (int j = 0; j < Global::BricksCountX; ++j, ++id) {
            sf::Vector2f pos{
                    Global::BricksGap + (float)j * (Global::BrickWidth + Global::BricksGap),
                    Global::BricksGap + (float)i * (Global::BrickHeight + Global::BricksGap)
            };
            
            if (id % 11 == 0) {
                bricks.emplace_front(std::make_shared<IndestructibleBrick>(*this, pos));
                continue;
            }
            if (id % 13 == 0) {
                bricks.emplace_front(std::make_shared<AccelerationBrick>(*this, pos));
                continue;
            }
            if (id % 17 == 0) {
                bricks.emplace_front(std::make_shared<BonusBrick>(*this, pos));
                continue;
            }
            
            bricks.emplace_front(std::make_shared<DefaultBrick>(*this, pos));
            
        }
    }

}

void GameInstance::SpawnBonus(const sf::Vector2f& position) {
    bonuses.emplace_back(std::make_shared<MovingBrickBonus>(*this, position));
}

void GameInstance::Speedup() {
    fps += Global::BallAcceleration;
}

void GameInstance::SpawnMovingBrick() {
    bricks.emplace_front(std::make_shared<MovingBrick>(*this));
}
