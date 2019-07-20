#pragma once
#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>


class Settings
{
public:
	double SoundVolume;
	double MusicVolume;
	std::string defaultMusic;
	int posDefaultMusic;
	Settings();
	void save();
	~Settings();
};

