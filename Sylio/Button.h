#pragma once
#include<SFML/Graphics.hpp>
#include"Sounds.h"
#include<iostream>

class Button
{
private:
	enum buttonState { isPressed, isNotPressed};
	enum positionState { isOn, isNotOn};
	static sf::RenderWindow& w;
	std::string text;
	sf::Sprite button;
	sf::Texture& pressed;
	sf::Texture& released;
	sf::RenderWindow& window;
	sf::Sprite &Mark;
	sf::Sound click;
	sf::Sound switchS;
	sf::Text title;
	sf::Font & font;
	positionState positionSt;
	positionState lastPositionSt;
	buttonState buttonSt;
	buttonState lastButtonSt;
	bool clicked;
public:
	Button(sf::RenderWindow& win, sf::Texture& pres, sf::Texture& rel, sf::Sprite& mark_, sf::SoundBuffer &click_, sf::SoundBuffer &switch_, sf::Font& font_);
	void showMark();
	void hideMark();
	void clickSound();
	void switchSound();
	bool buttonFunction();//return true if clicked out
	bool settingsListFunction();
	bool empty() { return text.empty(); }
	void setTitle(std::string title_);
	void setPosition(int posx, int posy);
	void draw() { window.draw(button); window.draw(title); };
	void checkState();
	void setColor(sf::Color x) { title.setFillColor(x); };
	void setSoundVolume(double v) { switchS.setVolume(30 * v); click.setVolume(v*100); }
	std::string& getString() { return text; }
	bool isOnButton();
	~Button();
};

