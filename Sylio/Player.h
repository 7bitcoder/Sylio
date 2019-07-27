#pragma once
#include <SFML/Graphics.hpp>
#include "Trace.h"
#include<random>

#define NINETY_DEG 1.57079633

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
	sf::Vector2f oldPosition;
	bool dead;
	int &xmax;
	int &xmin;
	int &ymax;
	int& ymin;
	sf::RenderTarget& board;
	double headR;
	Trace trace;
	int nextGap;
	int gapSize;
	sf::Vector2i gapBounds;
	sf::Vector2i NextGapounds;
	int actualGap;
public:
	void update();
	Player(sf::RenderWindow& win,double angle_, double R, double angvel, double vel, sf::Color col, sf::Keyboard::Key l, sf::Keyboard::Key r, int &ymax_, int & ymin_, int &xmax_, int &xmin_, sf::RenderTexture& board_);
	inline void setPosition(int x, int y) {
		position = sf::Vector2f(x, y); head.setPosition(position);	oldPosition = position;
		updateTrace();
	}
	void setNick(std::string str) { nickname = str; }
	void draw() { trace.draw();	window.draw(head);	}
	sf::Vector2f& getPos() { return position; }
	void die(bool x = true) { dead = true; }
	void checkBounds() { if (position.x < xmin || position.x > xmax || position.y > ymax || position.y < ymin) die(); }
	~Player();
	void setNewGap();
	void setGapBounds(int gbx, int gby, int ngbx, int ngby) {	gapBounds = { gbx,gby }; NextGapounds = { ngbx,ngby }; setNewGap();}
	inline void updateTrace() {
	float pointlx = headR * sin(angle + NINETY_DEG);
	float pointly = headR * cos(angle + NINETY_DEG);
	trace.update(sf::Vector2f(position.x + pointlx, position.y + pointly), sf::Vector2f(position.x - pointlx, position.y - pointly)); }
 };

