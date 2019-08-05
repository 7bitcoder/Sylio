#pragma once
#include <SFML/Graphics.hpp>
#include "Trace.h"
#include "settings.h"
#include<random>
#include <array>
#include "Boost.h"


extern Settings setting;
class Player
{
private:
	friend class Boost;
	friend class SpeedUp;
	friend class SlowDown;
	friend class GrowUp;
	friend class Shrink;
	friend class LockLeft;
	friend class LockRight;
	friend class Freeze;
	friend class SwitchControls;
	friend class Blind;
	static double rScan;
	int safety;
	int playerId;
	int nextGap;
	int gapSize;
	int actualGap;

	double angle;
	double angleVelocity;
	double velocity;
	double hiddenVelocity;
	double headR;
	double hiddenHeadR;
	double boostHeadTime;
	double boostTimeVel;

	bool dead;
	bool lockLeft;
	bool lockRight;
	bool freeze;
	bool visible;
	bool brokeWalls;
	bool activeBoost;
	int& xmax;
	int& xmin;
	int& ymax;
	int& ymin;

	std::vector<Boost *> boosts;

	sf::Color blendColor;
	std::array<std::array<int, 1920>, 1080>& hitbox;
	sf::RenderWindow& window;
	sf::Clock time;
	sf::CircleShape head;
	sf::CircleShape boosthead;
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
	static double getRScan() { return rScan; }
	void update();
	void draw() { if (visible) trace.draw();	window.draw(head); /*if (activeBoost) window.draw(boosthead);*/ }

	Player(std::vector<double>& headVec, std::array<std::array<int, 1920>, 1080>& hitbox_, sf::RenderWindow& win, sf::Color col, int& ymax_, int& ymin_, int& xmax_, int& xmin_, sf::RenderTexture& board_);
	void setGapBounds(int gbx, int gby, int ngbx, int ngby) { gapBounds = { gbx,gby }; NextGapounds = { ngbx,ngby }; setNewGap(); }
	void setParams(double angle_, double R, double angvel, double vel) { angle = angle_; changeRadious(R); hiddenHeadR = R; angleVelocity = angvel; velocity = vel; hiddenVelocity = vel; }
	void setNick(std::string str) { nickname = str; }
	void setControls(sf::Keyboard::Key l, sf::Keyboard::Key r) { left = l; right = r; }
	void setId(int id) { playerId = id; }
	void setColor(sf::Color col) { color = col; head.setFillColor(color); boosthead.setFillColor(sf::Color::White); }

	void checkBounds() { if (position.x - headR < xmin || position.x + headR > xmax || position.y + headR > ymax || position.y - headR < ymin) die(); }
	void addBoost(Boost* bost_); 
	void checkBoosts();
	void die(bool x = true) { dead = true; clearBoosts(); }
	bool getState() { return dead; }
	void clearBoosts() { for (auto& x : boosts) delete x; boosts.clear(); }
	void setNewGap();
	void drawLineOnHitBox(int x1, int y1);
	void Scan();
	void updateTrace();
	void erise();
	void roundPos() { roundPosition.x = round(position.x); roundPosition.y = round(position.y); }
	bool changeRadious(double R);
	sf::Vector2f& getPos() { return position; }

	inline void setPosition(sf::Vector2f pos) {
		position = pos;
		head.setPosition(position);	
		boosthead.setPosition(position);
		oldPosition = position;
		float pointlx = headR * sin(angle + NINETY_DEG);
		float pointly = headR * cos(angle + NINETY_DEG);
		sf::Vector2f xx(position.x + pointlx, position.y + pointly);
		sf::Vector2f yy(position.x - pointlx, position.y - pointly);
		trace.update(xx, yy);
		trace.start(headR, angle, position);
	}
	~Player();
};

