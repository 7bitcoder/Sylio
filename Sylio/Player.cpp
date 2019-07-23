#include "Player.h"
#include <cmath>


void Player::update()
{
	sf::Time t = time.getElapsedTime();
	time.restart();
	double r = velocity * t.asSeconds();
	if(sf::Keyboard::isKeyPressed(left))
		angle += angleVelocity * t.asSeconds();
	else if(sf::Keyboard::isKeyPressed(right))
		angle -= angleVelocity * t.asSeconds();
	position.x += r * sin(angle);
	position.y += r * cos(angle);
	head.setPosition(position);

}

Player::Player(sf::RenderWindow& win,double angle_, double R, double angvel, double vel, sf::Color col, sf::Keyboard::Key l, sf::Keyboard::Key r):window(win)
{
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
