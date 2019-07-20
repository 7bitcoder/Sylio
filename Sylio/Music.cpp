#include "Music.h"



Music::Music()
{
	if (!menuMusic.openFromFile("../DefaultMusic/Stranger_Things.wav"))
		exit(-1); // error
	menuMusic.setLoop(true);
	menuMusic.setVolume(30 * setting.MusicVolume);
	//menuMusic.play();
	if (!gameMusic.openFromFile("../DefaultMusic/Stranger_Things.wav"))
		exit(-1); // error
	gameMusic.setLoop(true);
	gameMusic.setVolume(30 * setting.MusicVolume);
}
bool Music::setGameMusic(std::string dir)
{
	return gameMusic.openFromFile("../Music/" + dir);
}

Music::~Music()
{
}
