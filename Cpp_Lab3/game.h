#pragma once

#include "gems.h"
#include "board.h"
#include "config.h"
#include <random>

#include <SFML\Graphics.hpp>

class Game
{
public:
	Game();
	~Game();
	bool init(GameConfiguration const& cfg);
	void loop();
private:
	bool setConfiguration(GameConfiguration const& cfg);

	sf::RenderWindow* m_window;
	sf::Text m_message;
	Board* m_board;
	int m_score;
	
};