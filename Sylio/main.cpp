#include "menu.h"
#include<string>
#include<SFML/Audio.hpp>
enum st { play = 1, settings, playOnline, quit, pause, menu } object;

int main()
{
	std::string version = "Beta 0.1";
	auto state = st::menu;
	sf::RenderWindow window(sf::VideoMode(1920 , 1080 ), "Sylio " + version , sf::Style::Fullscreen);
	Menu menu_(window, version);
	switch(state)
	{
	case st::menu :
		state = st(menu_.update());
		break;
	case st::quit :
		window.close();
		break;
	default:

		break;
	}
	return 0;
}