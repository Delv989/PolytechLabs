#include "board.h"
#include "bonus_test.h"

#include <utility>
#include <cstdlib>
#include <cmath>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <set>
#include <iostream>
#include <random>

ESprite Board::chooseColor(int i, int j) {
    ESprite color = static_cast<ESprite>(rand() % 5);
    return color;
}

sf::Vector2f Board::calculPosition(int i, int j) {
    return sf::Vector2f(x0 + Gem::GEM_SIZE / 2.0f + j * Gem::GEM_SIZE,
        y0 + Gem::GEM_SIZE / 2.0f + i * Gem::GEM_SIZE);
}

Board::Board(int x0, int y0, int width, int height)
    : x0(x0), y0(y0), width(width), height(height)
{
    this->m_board.resize(height);
    for (int i = 0; i < height; i++) {
        this->m_board.at(i).resize(width);
        for (int j = 0; j < width; j++) {
            sf::Vector2f pos(calculPosition(i, j));
            ESprite color = chooseColor(i, j);

            this->m_board.at(i).at(j) = new Gem(pos.x, pos.y, color);
        }
    }



}

Board::~Board() {
    for (auto& line : this->m_board)
        for (auto& gem : line)
            delete gem;
}

void Board::draw(sf::RenderWindow* window) {
    for (auto const& line : this->m_board)
        for (auto const& gem : line)
            gem->draw(window);
}

void Board::hoverEvent(sf::Event event, int ti, int tj, int& hi, int& hj, bool isTaken) {
    size_t i = (event.mouseMove.y - y0) / Gem::GEM_SIZE;
    size_t j = (event.mouseMove.x - x0) / Gem::GEM_SIZE;

    if (i < height && j < width) {
        if (!isTaken || ti != hi || tj != hj)
            m_board.at(hi).at(hj)->hover(false);

        m_board.at(i).at(j)->hover(true);
        hi = i;
        hj = j;
    }
}

bool isNeighbor(int ti, int tj, int hi, int hj) {
    return (std::abs(static_cast<int>(ti - hi)) == 1 &&
        std::abs(static_cast<int>(tj - hj)) == 0) ||
        (std::abs(static_cast<int>(ti - hi)) == 0 &&
            std::abs(static_cast<int>(tj - hj)) == 1);
}

void SwapGems(std::vector<std::vector<Gem*>>& gems, int i1, int j1, int i2, int j2) {
    sf::Vector2f pos = gems.at(i1).at(j1)->getPosition();
    gems.at(i1).at(j1)->setPosition(gems.at(i2).at(j2)->getPosition());
    gems.at(i2).at(j2)->setPosition(pos);
    std::swap(gems.at(i1).at(j1), gems.at(i2).at(j2));
}

bool Board::pressedEvent(bool& isTaken, int& ti, int& tj, int hi, int hj) {
    bool isSwapped = false;

    if (!isTaken) {
        ti = hi;
        tj = hj;
    }
    else if (isNeighbor(ti, tj, hi, hj)) {
        SwapGems(m_board, ti, tj, hi, hj);
        isSwapped = true;
    }

    isTaken = !isTaken;
    m_board.at(ti).at(tj)->hover(isTaken);
    m_board.at(hi).at(hj)->hover(isTaken);
    return isSwapped;
}

void Board::findSameColoredSequence(int gi, int gj, std::vector<std::pair<int, int>>& points) {
    std::set<std::pair<int, int>> visited;
    std::queue<std::pair<int, int>> queue;
    ESprite color = m_board.at(gi).at(gj)->getSprite();

    queue.push({gi, gj});

    std::pair<int, int> cur_gem;
    while (!queue.empty()) {
        cur_gem = queue.front();
        queue.pop();

        if (visited.find(cur_gem) == visited.end() && m_board.at(cur_gem.first).at(cur_gem.second)->getSprite() == color) {
            points.push_back(cur_gem);

            if (cur_gem.first < m_board.size() - 1) {
                queue.push({ std::min(cur_gem.first + 1, (int)m_board.size() - 1), cur_gem.second });
            }
            if (cur_gem.first > 0) {
                queue.push({ std::max(cur_gem.first - 1, 0), cur_gem.second });
            }
            if (cur_gem.second < m_board[0].size() - 1) {
                queue.push({ cur_gem.first, std::min(cur_gem.second + 1, (int)m_board[0].size() - 1)});
            }
            if (cur_gem.second > 0) {
                queue.push({ cur_gem.first, std::max(cur_gem.second - 1, 0) });
            }
        }
        visited.insert(cur_gem);
    }
}

bool Board::collisionGems(int gi, int gj) {

    std::vector<std::pair<int, int>> points;
    findSameColoredSequence(gi, gj, points);

    if (points.size() < 3) {
        return false;
    }

    for (auto& point : points) {
        m_board.at(point.first).at(point.second)->activate(m_board, point.first, point.second, width, height);
    }
    updateGems();

    std::uniform_real_distribution<float> distProcChance(0.0f, 1.0f);
    std::uniform_int_distribution<std::mt19937::result_type> distProcType(0, 1);
    Bonus* bonus = new Bonus();
    for(auto& point : points) {
        if (distProcChance(bonus->rndgen) < bonus->bonusChance) {
            if (distProcType(bonus->rndgen) == 0) {
                bonus = new Bomb(point.first, point.second);
            }
            else {
                bonus = new Recolor(point.first, point.second, m_board.at(point.first).at(point.second)->getSprite());
            }
            bonus->activate(this);
            updateGems();
        }
        

    }

    return true;
}

void Board::updateGems() {
    int find;
    for (int i = static_cast<int>(height - 1); i >= 0; i--) {
        for (int j = 0; j < width; j++) {
            if (m_board.at(i).at(j)->getSprite() == ESprite::S_NONE) {
                find = i - 1;

                while (find >= 0 && m_board.at(find).at(j)->getSprite() == ESprite::S_NONE)
                    --find;

                if (find >= 0)
                    SwapGems(m_board, i, j, find, j);
                else
                    
                    m_board.at(i).at(j)->setSprite(chooseColor(i,j));
            }
        }
    }
}



void Board::update(sf::Event event, int& score) {
    static bool isUpdated = true;
    static bool isTaken = false;
    static bool isSwapped = false;
    static int hover_i = 0, hover_j = 0;
    static int taken_i = 0, taken_j = 0;
    int dscore = 0;

    switch (event.type)
    {
    case sf::Event::MouseMoved:
        hoverEvent(event, taken_i, taken_j, hover_i, hover_j, isTaken);
        break;

    case sf::Event::MouseButtonPressed:
        isSwapped = pressedEvent(isTaken, taken_i, taken_j, hover_i, hover_j);
        break;

    default:
        break;
    }

    if (isSwapped) {
        dscore += collisionGems(static_cast<int>(hover_i), static_cast<int>(hover_j));
        dscore += collisionGems(static_cast<int>(taken_i), static_cast<int>(taken_j));

        if (dscore == 0)
            SwapGems(m_board, taken_i, taken_j, hover_i, hover_j);
        else
            isUpdated = false;

        isSwapped = false;
    }
    
    if (!isUpdated) {

        isUpdated = true;

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                ESprite color = m_board.at(i).at(j)->getSprite();
                std::vector<std::pair<int, int>> points;
                findSameColoredSequence(i, j, points);
                if (color != ESprite::S_NONE && points.size() >= 3) {
                    collisionGems(static_cast<int>(i), static_cast<int>(j));
                    isUpdated = false;
                }
            }

        }

    }

    
}