#include"settings.h"
#include"Music.h"
#include"Button.h"
#include<string>
#include<iostream>
#include<filesystem>
#include"list.h"
#include"Slider.h"
#include"Background.h"
#include "PopAlert.h"
#include "inputText.h"

extern Settings setting;
enum st { play = 1, settings, playOnline, quit, pause, mainMenu , normalGame, MultiGame};

class Menu
{
private:
	Background background;
	sf::RenderWindow& window;
	std::string & version;
	sf::Font font;
	sf::SoundBuffer clickBuff;
	sf::SoundBuffer switchBuff;
	sf::Texture back;
	sf::Texture base;
	//sf::Sprite background;
	sf::Texture mar;
	sf::Texture block;
	sf::Texture blockPressed;
	sf::Texture offButton;
	sf::Texture VolumeSliderLine;
	sf::Texture VolumePointner;
	sf::Texture listBlock;
	sf::Texture whiteBox;


public:
	Menu(sf::RenderWindow& win, std::string& ver);
	st mainMenuUpdate();
	st settingsUupdate();
	st normalGameUpdate();
	~Menu();
};

