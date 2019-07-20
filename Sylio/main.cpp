#include"Settings.h"
#include"Music.h"
#include"menu.h"
#include<string>
#include<SFML/Audio.hpp>
#include <filesystem>

Settings setting;
Music music;

int main()
{
	std::string version = "Beta 0.1";
	auto state = st::mainMenu;
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Sylio " + version , sf::Style::Fullscreen);
	music.playMenuMusic();
	Menu Menu_(window, version);

	while (true)
	{
		switch (state)
		{
		case st::mainMenu:
			state = Menu_.mainMenuUpdate();
			break;
		case st::settings:
			state = Menu_.settingsUupdate();
			break;
		case st::normalGame:
			state = Menu_.normalGameUpdate();
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
