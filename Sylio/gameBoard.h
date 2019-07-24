#pragma once
#include "Settings.h"

extern Settings setting;

class gameBoard
{
private:
	int xmax;
	int xmin;
	int ymin;
	int ymax;
	sf::RenderWindow& window;
	sf::RenderTexture board;
public:
	gameBoard(sf::RenderWindow &win);
	st update();
	~gameBoard();
};

