#include"Settings.h"
#include"Music.h"
#include"menu.h"
#include<string>
#include<SFML/Audio.hpp>
#include <filesystem>
#include "gameBoard.h"

Settings setting;
Music music;

int main()
{
	std::string version = "Beta 0.1";
	auto state = st::mainMenu;
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Sylio " + version , sf::Style::Fullscreen);
	music.playMenuMusic();
	Menu Menu_(window, version);
	sf::Image pointnerIm;
	if(!pointnerIm.loadFromFile("../PNG/pointner2.png"))
		std::cout << "error\n";
	sf::Cursor pointner;
	if(!pointner.loadFromPixels(pointnerIm.getPixelsPtr(), sf::Vector2u(30,31), sf::Vector2u(6,1)))
		exit(-1);
	window.setMouseCursor(pointner);
	gameBoard board(window);
	while (true)
	{
		switch (state)
		{
		case st::mainMenu:
			window.setMouseCursorVisible(true);
			state = Menu_.mainMenuUpdate();
			break;
		case st::settings:
			window.setMouseCursorVisible(true);
			state = Menu_.settingsUupdate();
			break;
		case st::normalGame:
			window.setMouseCursorVisible(true);
			state = Menu_.normalGameUpdate();
			break;
		case st::playNormalGame:
			window.setMouseCursorVisible(false);
			state = board.update();
			break;
		case st::quit:
			setting.save();
			window.close();
			return 0;
			break;
		default:

			break;
		}
	}
	return 0;
}
