#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
class inputText
{
private:
	static bool focused;
	sf::Text textOutput;
	enum buttonState { isPressed, isNotPressed };
	enum positionState { isOn, isNotOn };
	sf::Sprite box;
	sf::RenderWindow& window;
	positionState positionSt;
	positionState lastPositionSt;
	buttonState buttonSt;
	buttonState lastButtonSt;
	sf::Sound click;
	bool clicked;
	bool activated;
	std::string text;
	bool isOnButton();
	
public:
	inputText(sf::RenderWindow & win, sf::Texture & box_, sf::SoundBuffer & click);
	bool function();
	bool setChar(char t);
	void checkState();
	void draw() { window.draw(box); window.draw(textOutput); }
	void setPosition(int x, int y);
	void setColor(sf::Color x) { textOutput.setFillColor(x); }
	void setFont(sf::Font& x) { textOutput.setFont(x); }
	void setSize(int x) { textOutput.setCharacterSize(x); }
	void defaultString(std::string x);
	bool isActivated() { return isOn; }
	static bool getFocus() { return focused; }
	std::string& getText() { return text; }
	~inputText();
};

