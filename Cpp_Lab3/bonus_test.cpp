#include "bonus_test.h"
#include <random>
#include <iostream>
void Bomb::activate(Board* board) {
    std::vector<std::vector<Gem*>> gems = board->m_board;
    sf::Vector2f pos = gems.at(i).at(j)->getPosition();
    gems.at(i).at(j) = new Gem(pos.x, pos.y, ESprite::S_NONE);
	std::uniform_int_distribution<std::mt19937::result_type> distJ(0, board->width - 1);
	std::uniform_int_distribution<std::mt19937::result_type> distI(0, board->height - 1);

    for (int i = 0; i < 4; i++) {
        int ni = distI(rndgen);
		int nj = distJ(rndgen);

        gems.at(ni).at(nj)->activate(gems, ni, nj, board->width, board->height);
		

    }
	std::cout << "bomb\n";
}

void Recolor::activate(Board * board) {

	std::vector<std::vector<Gem*>> gems = board->m_board;
	std::uniform_int_distribution<std::mt19937::result_type> distJ(0, board->width - 1);
	std::uniform_int_distribution<std::mt19937::result_type> distI(0, board->height - 1);
	std::uniform_int_distribution<std::mt19937::result_type> distIinR(std::max(0, (i - radius)), std::min(i + radius, board->height - 1));
	std::uniform_int_distribution<std::mt19937::result_type> distJinR(std::max(0, (j - radius)), std::min(j + radius, board->width - 1));
	int cur_i = distIinR(rndgen);
	int cur_j = distJinR(rndgen);
	sf::Vector2f pos = gems.at(cur_i).at(cur_j)->getPosition();
	gems.at(cur_i).at(cur_j) = new Gem(pos.x, pos.y, color);
	int count = 0;
	while (count < 2) {
		cur_i = distI(rndgen);
		cur_j = distJ(rndgen);
		if ((abs(cur_i - i) > 1) || (abs(cur_j - j) > 1)) { 
			sf::Vector2f pos = gems.at(cur_i).at(cur_j)->getPosition();
			gems.at(cur_i).at(cur_j) = new Gem(pos.x, pos.y, color);
			count = count + 1;
		}
	}
	std::cout << "recolor\n";
}
