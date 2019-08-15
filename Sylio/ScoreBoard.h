#pragma once
#include <vector>
#include <queue>
#include <SFML/Graphics.hpp>
#include "Player.h"
struct data
{
	int score;
	std::string nickname;
	bool moving;
	int dest;
	bool main;
	int position;
	bool up;
	sf::Text text;
	sf::Clock timer;
};
class ScoreBoard
{
private:
	std::vector<int> positions;
	int posx;
	int charSize;
	sf::RenderWindow& window;
	std::vector<data> dates;
	std::vector<int> rank;
	std::queue<int> que;
	int main;
	float vel;
	bool updating;
public:
	void update();
	void updateScore(int id, Player& players);
	void draw();
	void move(int id);
	void checkColide();
	void setPosition(int x, int y, std::vector<Player>& players, sf::Font& font);
	void findPosition(int id);
	ScoreBoard( sf::RenderWindow& win, int size, float vel_);
	~ScoreBoard();
};

