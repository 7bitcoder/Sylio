#include "gameBoard.h"
#include "Player.h"
#include "players.h"
#include "Settings.h"

extern Settings setting;

gameBoard::gameBoard(sf::RenderWindow& win) :window(win)
{
	xmax = 1915;
	xmin = 300;
	ymin = 5;
	ymax = 1075;
	board.create(window.getSize().x, window.getSize().y);
	board.clear(sf::Color::Black);

}

st gameBoard::update()
{
	sf::Font font;
	if (!font.loadFromFile("../Font/kenvector_future.ttf"))
		exit(-1);

	sf::Text fps;
	fps.setFont(font);
	fps.setCharacterSize(40);
	fps.setPosition(20, 20);
	fps.setFillColor(sf::Color::White);
	sf::Clock timer;



	players Players(window, ymax, ymin, xmax, xmin, board);

	sf::Event event;


	int cnt = 0;
	timer.restart();
	while (window.isOpen())
	{
		Players.update();
		cnt++;
		if(timer.getElapsedTime().asMilliseconds() > 1000)
		{
			timer.restart();
			fps.setString(std::to_string(cnt));
			cnt = 0;
		}

		window.clear(sf::Color::Black); 
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			return st::mainMenu;

		//Players.draw();
		Players.draw();
		window.draw(fps);
		window.display();
	}
}


gameBoard::~gameBoard()
{
}
