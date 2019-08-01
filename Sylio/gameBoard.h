#pragma once
#include "Settings.h"

extern Settings setting;

class gameBoard
{
private:
	static std::array<std::array<int, 1920>, 1080> hitbox;
	int xmax;
	int xmin;
	int ymin;
	int ymax;
	int thicc;
	sf::Vertex bounds[4][4];
	sf::RenderWindow& window;
	sf::RenderTexture board;
public:
	gameBoard(sf::RenderWindow& win);
	st update();
	~gameBoard();
	void setBounds(int ymax_, int ymin_, int xmax_, int xmin_, int thicc);
	void drawBounds() {
		window.draw(bounds[0], 4, sf::Quads);
		window.draw(bounds[1], 4, sf::Quads);
		window.draw(bounds[2], 4, sf::Quads);
		window.draw(bounds[3], 4, sf::Quads);
	}
	void clearHitbox();
};

