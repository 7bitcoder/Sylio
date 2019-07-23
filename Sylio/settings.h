#pragma once
#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sfml/Graphics.hpp>
enum st { play = 1, settings, playOnline, quit, pause, mainMenu, normalGame, MultiGame, playNormalGame };
class Settings
{
public:
	struct playerStats
	{
		sf::Color color;
		std::string nickname;
		sf::Keyboard::Key left;
		sf::Keyboard::Key right;
	};
	double SoundVolume;
	double MusicVolume;
	int rounds;
	std::vector <playerStats> playersSettings;
	std::string defaultMusic;
	int posDefaultMusic;
	Settings();
	void save();
	~Settings();
};

