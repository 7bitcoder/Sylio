#pragma once
#include <SFML/Graphics.hpp>
#include "Trace.h"
#include<random>
#include <array>



class Player
{
private:
	static int rScan;
	int safety;
	int playerId;
	int nextGap;
	int gapSize;
	int actualGap;

	double angle;
	double angleVelocity;
	double velocity;
	double headR;

	bool dead;
	int& xmax;
	int& xmin;
	int& ymax;
	int& ymin;

	std::array<std::array<int, 1920>, 1080>& hitbox;
	sf::RenderWindow& window;
	sf::Clock time;
	sf::CircleShape head;
	std::string nickname;
	sf::Color color;
	sf::Keyboard::Key left;
	sf::Keyboard::Key right;
	sf::Vector2f position;
	sf::Vector2f oldPosition;
	sf::RenderTarget& board;
	sf::Vector2i gapBounds;
	sf::Vector2i NextGapounds;
	sf::Vector2i roundPosition;
	std::vector<double>& headVec;
	Trace trace;
public:
	void update();
	void draw() { trace.draw();	window.draw(head); }

	Player(std::vector<double>& headVec, std::array<std::array<int, 1920>, 1080>& hitbox_, sf::RenderWindow& win, sf::Color col, int& ymax_, int& ymin_, int& xmax_, int& xmin_, sf::RenderTexture& board_);
	void setGapBounds(int gbx, int gby, int ngbx, int ngby) { gapBounds = { gbx,gby }; NextGapounds = { ngbx,ngby }; setNewGap(); }
	void setParams(double angle_, double R, double angvel, double vel) { angle = angle_,changeRadious(R); angleVelocity = angvel; velocity = vel;	 }
	void setNick(std::string str) { nickname = str; }
	void setControls(sf::Keyboard::Key l, sf::Keyboard::Key r) { left = l; right = r; }
	void setId(int id) { playerId = id; }
	void setColor(sf::Color col) { color = col; head.setFillColor(color); }

	void checkBounds() { if (position.x - headR < xmin || position.x + headR > xmax || position.y + headR > ymax || position.y - headR < ymin) die(); }

	void die(bool x = true) { dead = true; }
	void setNewGap();
	void drawLineOnHitBox(int x1, int y1);
	void Scan();
	void updateTrace();
	void roundPos() { roundPosition.x = round(position.x); roundPosition.y = round(position.y); }
	void changeRadious(double R);
	sf::Vector2f& getPos() { return position; }

	inline void setPosition(int x, int y) {
		position = sf::Vector2f(x, y); head.setPosition(position);	oldPosition = position;
		float pointlx = headR * sin(angle + NINETY_DEG);
		float pointly = headR * cos(angle + NINETY_DEG);
		sf::Vector2f xx(position.x + pointlx, position.y + pointly);
		sf::Vector2f yy(position.x - pointlx, position.y - pointly);
		trace.update(xx, yy);
		trace.start(headR, angle);
	}
	~Player();
};

