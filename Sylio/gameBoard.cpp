#include "gameBoard.h"
#include "Player.h"
#include "Settings.h"

extern Settings setting;

gameBoard::gameBoard(sf::RenderWindow& win) :window(win)
{
	board.create(1000, 1000);
	board.clear(sf::Color::Black);

}

st gameBoard::update()
{
	std::vector<Player>players;
	int i = 0;
	for (auto& x : setting.playersSettings)
	{
		players.push_back(std::move(Player(window, 0, 5, 1.5, 100, x.color, x.left, x.right)));
		players.back().setPosition(300 + i*200, 100);
		players.back().setNick(x.nickname);
		i++;
	}
	sf::Event event;



	while (window.isOpen())
	{
		for (auto& player : players) player.update();
		window.clear(sf::Color::Black); 
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			return st::mainMenu;

		for (auto& player : players) player.draw();
		window.display();
	}
}


gameBoard::~gameBoard()
{
}
