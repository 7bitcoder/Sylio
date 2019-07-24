#include "Player.h"
#include <cmath>

#define NINETY_DEG 1.57079633

void Player::update()
{
	if (!dead)
	{
		sf::Time t = time.getElapsedTime();
		time.restart();
		double r = velocity * t.asSeconds();
		if (sf::Keyboard::isKeyPressed(left))
			angle += angleVelocity * t.asSeconds();
		else if (sf::Keyboard::isKeyPressed(right))
			angle -= angleVelocity * t.asSeconds();
		position.x += r * sin(angle);
		position.y += r * cos(angle);
		head.setPosition(position);
	}
}

Player::Player(sf::RenderWindow& win,double angle_, double R, double angvel, double vel, sf::Color col, sf::Keyboard::Key l, sf::Keyboard::Key r, int& ymax_, int& ymin_, int& xmax_, int& xmin_, sf::RenderTexture& board_):
window(win),
xmax(xmax_),
xmin(xmin_),
ymax(ymax_),
ymin(ymin_),
board(board_)
{
	dead = false;
	angle = angle_;
	velocity = vel;
	angleVelocity = angvel;
	time.restart();
	color = col;
	head.setFillColor(color);
	position = { 1000, 1000 };
	head.setPosition(position);
	head.setRadius(R);
	head.setOrigin(R, R);
	left = l;
	right = r;
}


Player::~Player()
{
}
