#include "players.h"

players::players(sf::RenderWindow& win, int ymax_, int ymin_, int xmax_, int xmin_, sf::RenderTexture& board_) : window(win), board(board_)
{

	thicc = 5;
	setBounds(ymax_, ymin_, xmax_, xmin_);
	int i = 0;
	/*for (auto& x : setting.playersSettings)
	{
		Players.push_back(std::move(Player(window, 0, 5, 1.5, 100, x.color, x.left, x.right, ymax, ymin, xmax, xmin, board)));
		Players.back().setPosition(600 + i * 200, 100);
		Players.back().setNick(x.nickname);
		i++;
	}*/
	Players.push_back(std::move(Player(window, 0, 5, 1.5, 100, sf::Color::Red, sf::Keyboard::Key::S, sf::Keyboard::Key::D, ymax, ymin, xmax, xmin, board)));
	Players.back().setPosition(700 , 100);
	Players.back().setNick("sylwek");
}

void players::setBounds(int ymax_, int ymin_, int xmax_, int xmin_)
{
	xmax = xmax_;
	xmin = xmin_;
	ymin = ymin_;
	ymax = ymax_;

	bounds[0][0] = sf::Vertex(sf::Vector2f(xmax + thicc, ymin - thicc), sf::Color::Yellow);
	bounds[0][1] = sf::Vertex(sf::Vector2f(xmax, ymin), sf::Color::Yellow);
	bounds[0][2] = sf::Vertex(sf::Vector2f(xmax, ymax), sf::Color::Yellow);
	bounds[0][3] = sf::Vertex(sf::Vector2f(xmax + thicc, ymax + thicc), sf::Color::Yellow);

	bounds[1][0] = sf::Vertex(sf::Vector2f(xmax + thicc, ymax + thicc), sf::Color::Yellow);
	bounds[1][1] = sf::Vertex(sf::Vector2f(xmax, ymax), sf::Color::Yellow);
	bounds[1][2] = sf::Vertex(sf::Vector2f(xmin, ymax), sf::Color::Yellow);
	bounds[1][3] = sf::Vertex(sf::Vector2f(xmin - thicc, ymax + thicc), sf::Color::Yellow);

	bounds[2][0] = sf::Vertex(sf::Vector2f(xmin - thicc, ymax + thicc), sf::Color::Yellow);
	bounds[2][1] = sf::Vertex(sf::Vector2f(xmin, ymax), sf::Color::Yellow);
	bounds[2][2] = sf::Vertex(sf::Vector2f(xmin, ymin), sf::Color::Yellow);
	bounds[2][3] = sf::Vertex(sf::Vector2f(xmin - thicc, ymin - thicc), sf::Color::Yellow);

	bounds[3][0] = sf::Vertex(sf::Vector2f(xmin - thicc, ymin - thicc), sf::Color::Yellow);
	bounds[3][1] = sf::Vertex(sf::Vector2f(xmin, ymin), sf::Color::Yellow);
	bounds[3][2] = sf::Vertex(sf::Vector2f(xmax, ymin), sf::Color::Yellow);
	bounds[3][3] = sf::Vertex(sf::Vector2f(xmax + thicc, ymin - thicc), sf::Color::Yellow);

}

players::~players()
{
}
