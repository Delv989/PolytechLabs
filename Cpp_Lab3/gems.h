#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

enum class ESprite {
	S_RED = 0,
	S_GREEN,
	S_YELLOW,
	S_PURPLE,
	S_BLUE,
	S_NONE
};


class Gem
{
public:
	static sf::Texture SPRITE;
	static float ONE_SPRITE_WIDTH;
	static int GEM_SIZE;

	Gem(float x, float y, ESprite sprite);

	ESprite getSprite() const;
	sf::Vector2f getPosition() const;

	void setSprite(ESprite sprite);
	void hover(bool isHover);

	void setPosition(sf::Vector2f pos);
	void draw(sf::RenderWindow* window) const;
	void activate(std::vector<std::vector<Gem*>>& gems, int i, int j, int width, int height);

private:
	ESprite m_sprite;
	sf::RectangleShape m_gem;
};
