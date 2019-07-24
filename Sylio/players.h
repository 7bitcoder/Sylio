#pragma once
#include"Player.h"
#include "Settings.h"
#include <iostream>

extern Settings setting;

class players
{
private:
	sf::RenderTexture& board;
	sf::Vertex bounds[4][4];
	sf::RenderWindow& window;
	std::vector<Player> Players;
	int xmax;
	int xmin;
	int ymin;
	int ymax;
	int thicc;
public:
	players(sf::RenderWindow & win, int ymax, int ymin, int xmax, int xmin, sf::RenderTexture& board_);
	inline void update() {
		for (auto& player : Players)
		{
			player.update();
			player.checkBounds();
		}
	}
	inline void draw(void) {
		window.draw(bounds[0], 4, sf::Quads);
		window.draw(bounds[1], 4, sf::Quads);
		window.draw(bounds[2], 4, sf::Quads);
		window.draw(bounds[3], 4, sf::Quads);
		for (auto& player : Players)
			player.draw();
	};
	void setBounds(int ymax, int ymin, int xmax, int xmin);
	~players();
};

