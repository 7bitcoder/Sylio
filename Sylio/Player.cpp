#include "Player.h"
#include <cmath>
#include <iostream>
#include <fstream>
//kat zmniejsza sie zgodnie z wsk zegara


double Player::rScan = 40;
void Player::update()
{
	if (!dead)
	{
		sf::Time t = time.getElapsedTime();
		time.restart();
		if (!setting.TimeStop)
		{
			double r = velocity * t.asSeconds();
			if (sf::Keyboard::isKeyPressed(left))
				if (sf::Keyboard::isKeyPressed(right));
				else
					angle += angleVelocity * t.asSeconds();
			else if (sf::Keyboard::isKeyPressed(right))
				angle -= angleVelocity * t.asSeconds();
			//std::cout << pointx << "    " << pointy << "\n";
			if (angle > 4 * NINETY_DEG)
				angle -= 4 * NINETY_DEG;
			position.x += r * sin(angle);
			position.y += r * cos(angle);
			head.setPosition(position);

			int diff = (oldPosition.x - position.x) * (oldPosition.x - position.x) + (oldPosition.y - position.y) * (oldPosition.y - position.y);
			if (diff > 4)
			{

				if (trace.getState() && actualGap > nextGap)
				{
					actualGap = 0;
					trace.stop(headR, angle);
				}
				else if (!trace.getState() && actualGap > gapSize)
				{
					actualGap = 0;
					setNewGap();
					updateTrace();
					trace.start(headR, angle);
				}
				else if (trace.getState()) {
					updateTrace();
					roundPos();
					Scan();
					drawLineOnHitBox(round(oldPosition.x), round(oldPosition.y));
				}
				actualGap += diff;
				oldPosition = position;
			}
		}
	}
}

Player::Player(std::vector<double>& headVec_,std::array<std::array<int, 1920>, 1080>& hitbox_, sf::RenderWindow& win, sf::Color col, int& ymax_, int& ymin_, int& xmax_, int& xmin_, sf::RenderTexture& board_) :
	window(win),
	xmax(xmax_),
	xmin(xmin_),
	ymax(ymax_),
	ymin(ymin_),
	board(board_),
	hitbox(hitbox_),
	headR(0),
	angle(0),
	headVec(headVec_),
	trace(win, col, 8000000, 10000)
{
	dead = false;
	std::cout << "rozmiar :" << sizeof(sf::Vertex) << std::endl;
	time.restart();
	color = col;
	head.setFillColor(color);
	actualGap = 0;
	srand(std::time(0));
	safety = 2;
}

Player::~Player()
{
	for (auto &  x : boosts)
		delete x;
	std::cout << "size of tail :" << trace.getIndex() << std::endl << "fragments Size :" << trace.getFragmentsSize() <<std::endl;
}

void Player::checkBoosts()
{
	std::vector<Boost *>::iterator it;
	bool found = false;
	for (auto itt = boosts.begin(); itt != boosts.end() ; itt++)
	{
		if ((*itt)->check())
		{
			found = true;
			it = itt;
			(*itt)->clearBoost(*this);
			delete (*itt);
			std::cout << "del :" << velocity << std::endl;
			break;
		}
	}
	if(found)
		boosts.erase(it);
}

void Player::setNewGap()
{
	gapSize = gapBounds.x + rand() % (gapBounds.y - gapBounds.x);
	nextGap = NextGapounds.x + rand() % (NextGapounds.y - NextGapounds.x);
}
void Player::drawLineOnHitBox(int x1, int y1)
{
	int x0 = roundPosition.x;
	int y0 = roundPosition.y;
	int val = playerId << 28;
	val |= int(round(headR));

	int dx = abs(x1 - x0);
	int sx = x0 < x1 ? 1 : -1;
	int dy = -abs(y1 - y0);
	int sy = y0 < y1 ? 1 : -1;
	int err = dx + dy;  /* error value e_xy */
	while (true)   /* loop */
	{
		if (x0 == x1 && y0 == y1) break;
		int e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy; /* e_xy+e_x > 0 */
			x0 += sx;
		}
		if (e2 <= dx) /* e_xy+e_y < 0 */
		{
			err += dx;
			y0 += sy;
		}
		hitbox[y0][x0] = val;
	}
}
void Player::Scan()
{
	int leftpointx = round(headR * sin(angle + SEE_RANGE) + position.x);
	int leftpointy = round(headR * cos(angle + SEE_RANGE) + position.y);

	int rightpointx = round(headR * sin(angle - SEE_RANGE) + position.x);
	int rightpointy = round(headR * cos(angle - SEE_RANGE) + position.y);

	/*int lx = round(L.x);
	int ly = round(L.y);
	int rx = round(R.x);
	int ry = round(R.y);


	int B = lx - rx;//-dx
	 int A = ry - ly;//dy
	 int C = ly*(-B) - lx *(A);

	*/
	int BLc = leftpointx - roundPosition.x;//-dx
	int ALc = roundPosition.y - leftpointy;//dy
	int CLc = leftpointy * (-BLc) - leftpointx * (ALc);

	int BRc = roundPosition.x - rightpointx;//-dx
	int ARc = rightpointy - roundPosition.y;//dy
	int CRc = roundPosition.y * (-BRc) - roundPosition.x * (ARc);

	int r = round(rScan);

	int begx = roundPosition.x - r;
	if (begx < xmin)
		begx = xmin;
	int begy = roundPosition.y - r;
	if (begy < ymin)
		begy = ymin;
	int endx = roundPosition.x + r;
	if (endx > xmax)
		endx = xmax;
	int endy = roundPosition.y + r;
	if (endy > ymax)
		endy = ymax;

	for (int x = begx; x <= endx; x++)
	{
		for (int y = begy; y <= endy; y++)
		{
			if (ALc * x + BLc * y + CLc >= 0 || ARc * x + BRc * y + CRc >= 0)
			{
				//std::cout << 'x';
				if (!hitbox[y][x])
					continue;
				else
				{
					int hitboxVal = hitbox[y][x];
					int id = hitboxVal >> 28;
					int R = hitboxVal & 0xFFFFF;
					if ((R + headR) * (R + headR) > (double(roundPosition.x) - x) * (double(roundPosition.x) - x) + (double(roundPosition.y) - y) * (double(roundPosition.y) - y))
					{
						die();
						std::ofstream myfile("example.txt");
						for (int i = begy; i <= endy;i++)
						{
							for (int j = begx; j <= endx; j++)
							{
								if(!hitbox[i][j])
									myfile << '_';
								else
								{
									if (j == roundPosition.x && i == roundPosition.y)
										myfile << 'O';
									else if (j == x && i == y)
										myfile << '8';
									else
										myfile << 'X';
								}
							}
							myfile << std::endl;
						}
						myfile.close();
						
					}
					else//ew warunek immortal
					{
						;
					}
				}
			}
			//std::cout << "_";
		}
	//std::cout << std::endl;
	}
	//std::cout << std::endl;
}

inline void Player::updateTrace()
{
	float pointlx = headR * sin(angle + NINETY_DEG);
	float pointly = headR * cos(angle + NINETY_DEG);
	sf::Vector2f pointx(position.x + pointlx, position.y + pointly);
	sf::Vector2f pointy(position.x - pointlx, position.y - pointly);
	trace.update(pointx, pointy);
}

void Player::changeRadious(double R)
{
	headR = R;
	head.setRadius(R); 
	head.setOrigin(R, R);
	headVec[playerId - 1] = R;
	double max = 0;
	for (auto& x : headVec)
	{
		if (x > max)
			max = x;
	}
	rScan = max + 3;
}
