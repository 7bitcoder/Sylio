#include "Player.h"
#include <cmath>
#include <iostream>

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

		//std::cout << pointx << "    " << pointy << "\n";
		if ((oldPosition.x - position.x) * (oldPosition.x - position.x) + (oldPosition.y - position.y) * (oldPosition.y - position.y) > 10)
		{
			float pointlx = headR * sin(angle + NINETY_DEG);
			float pointly = headR * cos(angle + NINETY_DEG);

			float pointrx = headR * sin(angle - NINETY_DEG);
			float pointry = headR * cos(angle - NINETY_DEG);
			sf::Vertex tmp[2] = { sf::Vertex(sf::Vector2f(pointrx, pointry) + position, color) , sf::Vertex(sf::Vector2f(pointlx, pointly) + position, color) };
			trace.push_back(tmp[0]);
			trace.push_back(tmp[1]);
			oldPosition = position;
			/*if (traceBuff.update(&tmp[0],2,trace.size()-3)){
				//std::cout << "tak";
			}*/
			//std::cout << traceBuff.getVertexCount() <<"  "<< trace.size()<< std::endl;
		}
	}
}

Player::Player(sf::RenderWindow& win, double angle_, double R, double angvel, double vel, sf::Color col, sf::Keyboard::Key l, sf::Keyboard::Key r, int& ymax_, int& ymin_, int& xmax_, int& xmin_, sf::RenderTexture& board_) :
	window(win),
	xmax(xmax_),
	xmin(xmin_),
	ymax(ymax_),
	ymin(ymin_),
	board(board_),
	traceBuff(sf::TrianglesStrip, sf::VertexBuffer::Usage::Stream)
{
	trace.reserve(8000000);
	std::cout << "rozmiar :" << trace.capacity()*sizeof(sf::Vertex)/(8*1000*1000) <<" MB"<< std::endl;
	dead = false;
	if (!sf::VertexBuffer::isAvailable())
		exit(-1);
	if (!traceBuff.create(100000))
		exit(-1);
	//std::cout << "rozmiar :" << traceBuff.getUsage() * sizeof(sf::Vertex) / (8 * 1000 * 1000) << " MB" << std::endl;

	angle = angle_;
	velocity = vel;
	angleVelocity = angvel;
	time.restart();
	color = col;
	head.setFillColor(color);
	position = { 1000, 1000 };
	oldPosition = position;
	head.setPosition(position);
	head.setRadius(R);
	head.setOrigin(R, R);
	left = l;
	right = r;
	headR = R;
}

Player::~Player()
{
}
