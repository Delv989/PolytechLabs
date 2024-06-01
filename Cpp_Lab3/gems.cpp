#include "gems.h"
#include <iostream>

sf::Texture Gem::SPRITE;
float Gem::ONE_SPRITE_WIDTH;
int Gem::GEM_SIZE;

Gem::Gem(float x, float y, ESprite sprite) : m_sprite(sprite) {
    sf::Vector2f size(Gem::ONE_SPRITE_WIDTH, Gem::ONE_SPRITE_WIDTH);

    this->m_gem.setSize(size);
    this->m_gem.setOrigin(size / 2.f);

    switch (static_cast<int>(sprite))
    {
    case 0:
        this->m_gem.setFillColor(sf::Color::Red);
        break;
    case 1:
        this->m_gem.setFillColor(sf::Color::Green);
        break;
    case 2:
        this->m_gem.setFillColor(sf::Color::Yellow);
        break;
    case 3:
        this->m_gem.setFillColor(sf::Color::Magenta);
        break;
    case 4:
        this->m_gem.setFillColor(sf::Color::Blue);
        break;
    default:
        this->m_gem.setFillColor(sf::Color::Black);
        break;
    }

    this->m_gem.setPosition(x, y);
}

void Gem::setSprite(ESprite sprite) {
    this->m_sprite = sprite;

    switch (static_cast<int>(sprite))
        {
        case 0:
            this->m_gem.setFillColor(sf::Color::Red);
            break;
        case 1:
            this->m_gem.setFillColor(sf::Color::Green);
            break;
        case 2:
            this->m_gem.setFillColor(sf::Color::Yellow);
            break;
        case 3:
            this->m_gem.setFillColor(sf::Color::Magenta);
            break;
        case 4:
            this->m_gem.setFillColor(sf::Color::Blue);
            break;
        default:
            this->m_gem.setFillColor(sf::Color::Black);
            break;

        }
    
}
void Gem::activate(std::vector<std::vector<Gem*>>& gems, int i, int j, int width, int height) {
    gems.at(i).at(j)->setSprite(ESprite::S_NONE);
    return;
}

void Gem::hover(bool isHover) {
    if (isHover)
        this->m_gem.setScale(0.9f, 0.9f);
    else
        this->m_gem.setScale(1.f, 1.f);
}

sf::Vector2f Gem::getPosition() const {
    return this->m_gem.getPosition();
}

void Gem::setPosition(sf::Vector2f pos) {
    this->m_gem.setPosition(pos);
}

ESprite Gem::getSprite() const {
    return m_sprite;
}

void Gem::draw(sf::RenderWindow* window) const {
    window->draw(this->m_gem);
}