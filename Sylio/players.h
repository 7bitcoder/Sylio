#pragma once
#include"Player.h"
#include "Settings.h"
#include <iostream>
#include <array>

extern Settings setting;

class players
{
private:
	std::array<std::array<int, 1920>, 1080>& hitbox;
	sf::RenderTexture& board;
	sf::RenderWindow& window;
	std::vector<Player> Players;
	std::vector<double> allHeadRadious;
	int& xmax;
	int& xmin;
	int& ymin;
	int& ymax;
	int& thicc;
public:
	players(std::array<std::array<int, 1920>, 1080>& hitbox_, sf::RenderWindow& win, int& ymax, int& ymin, int& xmax, int& xmin, int& thicc, sf::RenderTexture& board_);
	inline void update() {
		for (auto& player : Players)
		{
			player.update();
			player.checkBounds();
		}
	}
	inline void draw(void) {
		for (auto& player : Players)
			player.draw();
	};
	~players();
};

