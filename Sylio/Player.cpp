#include "Player.h"
#include <cmath>
#include <iostream>
//kat zmniejsza sie zgodnie z wsk zegara


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
		//std::cout << pointx << "    " << pointy << "\n";
		position.x += r * sin(angle);
		position.y += r * cos(angle);

		int diff = (oldPosition.x - position.x) * (oldPosition.x - position.x) + (oldPosition.y - position.y) * (oldPosition.y - position.y);
		if (diff > 10)
		{
			head.setPosition(position);
			//std::cout << traceBuff.getVertexCount() <<"  "<< trace.size()<< std::endl;
			//actualGap += diff;
			oldPosition = position;
			/*if (trace.getState() && actualGap > nextGap)
			{
				trace.stop();
				actualGap = 0;
				//std::cout <<nextGap<< " stop\n";
			}
			if (!trace.getState() && actualGap > gapSize)
			{
				trace.start();
				actualGap = 0;
				setNewGap();
				//updateTrace();
				//std::cout <<gapSize<< " start\n";
			}*/
			//if (trace.getState()) {
				//updateTrace();
				//std::cout << angle << std::endl;
			//}
		}
	}
}

Player::Player(sf::RenderWindow& win, double angle_, double R, double angvel, double vel, sf::Color col, sf::Keyboard::Key l, sf::Keyboard::Key r, int& ymax_, int& ymin_, int& xmax_, int& xmin_, sf::RenderTexture& board_) :
	window(win),
	xmax(xmax_),
	xmin(xmin_),
	ymax(ymax_),
	ymin(ymin_),
	board(board_)
	//trace(win, col, 80000, 10000)
{
	dead = false;
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
	actualGap = 0;
	srand(std::time(0));
}

void Player::setPosition(int x, int y)
{
	 position = sf::Vector2f(x, y); head.setPosition(position);	oldPosition = position; 
	 //updateTrace();
}

Player::~Player()
{
}

void Player::setNewGap()
{
	gapSize = gapBounds.x +  rand() % (gapBounds.y - gapBounds.x);
	nextGap = NextGapounds.x + rand() % (NextGapounds.y - NextGapounds.x);
}
