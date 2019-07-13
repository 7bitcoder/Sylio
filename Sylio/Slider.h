#pragma once
#include"settings.h"
#include<SFML/Graphics.hpp>
#include"Sounds.h"
#include"Music.h"
extern Settings setting;
extern Music music;
class Slider
{
private:
	enum pointnerState { isOn = 1, isNotOn, isPressed, isNotPressed, apperedOn, isClickedOn, isClickedOut, apperedOut, notClickedOutButCoursorIsOut };
	int id;//do rozdzielenia slidera music od sound
	sf::Sprite pointner;
	sf::Sprite line;
	sf::RenderWindow& window;
	sf::Sound click;
	pointnerState state;
	bool isAlredyOnButton;
	bool mouseAlredyPressed;
	bool isAlredyOut;
	bool isOnPointner();
	double vol;
public:
	void checkState();
	bool sliderFunction();
	Slider(sf::RenderWindow& win, sf::Texture& pointner_, sf::Texture& line_, sf::SoundBuffer &click_);
	void setPosition(int x, int y, int id_);
	void draw() { window.draw(line); window.draw(pointner); };
	void setSoundVolume(double v) { click.setVolume(v*100); }
	~Slider();
};

