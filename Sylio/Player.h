#pragma once
#include <SFML/Graphics.hpp>
class Player
{
private:
	sf::RenderWindow& window;
	sf::Clock time;
	sf::CircleShape head;
	double angle;
	double angleVelocity;
	double velocity;
	std::string nickname;
	sf::Color color;
	sf::Keyboard::Key left;
	sf::Keyboard::Key right;
	sf::Vector2f position;
public:
	void update();
	Player(sf::RenderWindow& win,double angle_, double R, double angvel, double vel, sf::Color col, sf::Keyboard::Key l, sf::Keyboard::Key r);
	void setPosition(int x, int y) { position = sf::Vector2f(x,y); head.setPosition(position); }
	void setNick(std::string str) { nickname = str; }
	void draw() { window.draw(head); }
	~Player();
};

