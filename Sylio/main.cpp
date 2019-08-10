#include"Settings.h"
#include"Music.h"
#include"menu.h"
#include<string>
#include<SFML/Audio.hpp>
#include <filesystem>
#include <thread>
#include <atomic>
#include "gameBoard.h"
#include"loadingScreen.h"

Settings setting;
Music music;
/*
pamietaj ze przy krawedzi hitboxa jest odstep i

*/
int main()
{
	std::cout << sizeof(long long int) << std::endl;
	sf::ContextSettings set;
	set.antialiasingLevel = 8;
	std::string version = "Beta 0.1";
	auto state = st::mainMenu;
	
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Sylio " + version, sf::Style::Fullscreen, set);
	window.clear(sf::Color::Black);
	std::atomic_flag endThread;
	endThread.test_and_set();
	loadingScreen loadingScr(window, endThread);
	window.setActive(false);
	std::thread thd(loadingScr);
	music.playMenuMusic();

	Menu Menu_(window, version);
	sf::Image pointnerIm;
	if (!pointnerIm.loadFromFile("../PNG/pointner2.png"))
		std::cout << "error\n";
	sf::Cursor pointner;
	if (!pointner.loadFromPixels(pointnerIm.getPixelsPtr(), sf::Vector2u(30, 31), sf::Vector2u(6, 1)))
		exit(-1);
	window.setMouseCursor(pointner);
	window.setMouseCursorVisible(false);

	gameBoard board(window);
	
	endThread.clear();
	thd.join();
	
	window.setActive(true);
	window.setMouseCursorVisible(true);
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