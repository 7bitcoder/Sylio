#pragma once
#include "Settings.h"

extern Settings setting;

class gameBoard
{
private:
	sf::RenderWindow& window;
	sf::RenderTexture board;
public:
	gameBoard(sf::RenderWindow &win);
	st update();
	~gameBoard();
};

