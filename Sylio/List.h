#pragma once
#include<SFML/Graphics.hpp>
#include<vector>
#include<string>
#include"Button.h"
#include"Sounds.h"

class List
{
private:
	std::vector<Button> list;
	std::string chosenFile;
	public:
	List();
	void pushBack( sf::RenderWindow& win, sf::Texture& pres, sf::Texture& rel, sf::Sprite& mark_, sf::SoundBuffer &click_, sf::SoundBuffer &switch_, sf::Font& font_);
	~List();
	void setText(std::string text) { list.back().setTitle(text); };
	void checkState();
	void draw() { for (auto& x : list) x.draw(); }
	void setScale(double x, double y) { list.back().setScale(x, y); }
	void setPosition(int x, int y) { list.back().setPosition(x, y); };
	void setSoundVolume(double v) { for (auto& x : list)x.setSoundVolume(v); }
	std::string& getFileDirect() { return chosenFile; }
};

