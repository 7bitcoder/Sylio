#include "gameBoard.h"
#include "Player.h"
#include "players.h"
#include "Settings.h"

extern Settings setting;
std::array<std::array<int, 1920>, 1080> gameBoard::hitbox = { 0 };
gameBoard::gameBoard(sf::RenderWindow& win) :window(win)
{
	setBounds(1075, 5, 1915, 300, 5);
	board.create(window.getSize().x, window.getSize().y);
	board.clear(sf::Color::Black);

}

st gameBoard::update()
{
	clearHitbox();

	sf::Font font;
	if (!font.loadFromFile("../Font/kenvector_future.ttf"))
		exit(-1);

	sf::Text fps;
	fps.setFont(font);
	fps.setCharacterSize(40);
	fps.setPosition(20, 20);
	fps.setFillColor(sf::Color::White);
	sf::Clock timer;

	players Players(hitbox,window, ymax, ymin, xmax, xmin,thicc, board);
	sf::Event event;

	int cnt = 0;
	timer.restart();
	while (window.isOpen())
	{
		Players.update();
		cnt++;
		if(cnt == 200)
		{
			fps.setString(std::to_string(int(cnt/timer.getElapsedTime().asSeconds())));
			timer.restart();
			cnt = 0;
		}

		window.clear(sf::Color::Black); 
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			return st::mainMenu;

		//Players.draw();
		drawBounds();
		Players.draw();
		window.draw(fps);
		window.display();
	}
}


gameBoard::~gameBoard()
{
}
void gameBoard::setBounds(int ymax_, int ymin_, int xmax_, int xmin_, int thicc_)
{
	xmax = xmax_;
	xmin = xmin_;
	ymin = ymin_;
	ymax = ymax_;
	thicc = thicc_;
	bounds[0][0] = sf::Vertex(sf::Vector2f(xmax + thicc, ymin - thicc), sf::Color::White);
	bounds[0][1] = sf::Vertex(sf::Vector2f(xmax, ymin), sf::Color::White);
	bounds[0][2] = sf::Vertex(sf::Vector2f(xmax, ymax), sf::Color::White);
	bounds[0][3] = sf::Vertex(sf::Vector2f(xmax + thicc, ymax + thicc), sf::Color::White);

	bounds[1][0] = sf::Vertex(sf::Vector2f(xmax + thicc, ymax + thicc), sf::Color::White);
	bounds[1][1] = sf::Vertex(sf::Vector2f(xmax, ymax), sf::Color::White);
	bounds[1][2] = sf::Vertex(sf::Vector2f(xmin, ymax), sf::Color::White);
	bounds[1][3] = sf::Vertex(sf::Vector2f(xmin - thicc, ymax + thicc), sf::Color::White);

	bounds[2][0] = sf::Vertex(sf::Vector2f(xmin - thicc, ymax + thicc), sf::Color::White);
	bounds[2][1] = sf::Vertex(sf::Vector2f(xmin, ymax), sf::Color::White);
	bounds[2][2] = sf::Vertex(sf::Vector2f(xmin, ymin), sf::Color::White);
	bounds[2][3] = sf::Vertex(sf::Vector2f(xmin - thicc, ymin - thicc), sf::Color::White);

	bounds[3][0] = sf::Vertex(sf::Vector2f(xmin - thicc, ymin - thicc), sf::Color::White);
	bounds[3][1] = sf::Vertex(sf::Vector2f(xmin, ymin), sf::Color::White);
	bounds[3][2] = sf::Vertex(sf::Vector2f(xmax, ymin), sf::Color::White);
	bounds[3][3] = sf::Vertex(sf::Vector2f(xmax + thicc, ymin - thicc), sf::Color::White);

}

void gameBoard::clearHitbox()
{
		for (auto& x : hitbox)
			for (auto& y : x)
				y = 0;
}
