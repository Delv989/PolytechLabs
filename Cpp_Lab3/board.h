#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "gems.h"

class Gem;

class Board
{
public:
	explicit Board(int x, int y, int width, int height);
	~Board();

	void draw(sf::RenderWindow* window);
	void update(sf::Event event, int& score);

	size_t x0, y0;
	int width, height;

	bool collisionGems(int gi, int gj);
	sf::Vector2f calculPosition(int i, int j);
	void hoverEvent(sf::Event event, int ti, int tj, int& hi, int& hj, bool isTaken);
	bool pressedEvent(bool& isTaken, int& ti, int& tj, int hi, int hj);
	void findSameColoredSequence(int gi, int gj, std::vector<std::pair<int, int>>& points);
	ESprite chooseColor(int i, int j);
	void updateGems();

	std::vector<std::vector<Gem*>> m_board;

};
