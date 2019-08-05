#include "gameBoard.h"


std::array<std::array<int, 1920>, 1080> gameBoard::hitbox = { 0 };
gameBoard::gameBoard(sf::RenderWindow& win) :window(win)
{
	setBounds(1075, 5, 1915, 300, 5);
	board.create(window.getSize().x, window.getSize().y);
	board.clear(sf::Color::Black);
	srand(std::time(0));
	boostR = 10;
}

st gameBoard::update()
{
	clearHitbox();

	sf::Font font;
	if (!font.loadFromFile("../Font/kenvector_future.ttf"))
		exit(-1);

	sf::Text fps;
	fps.setFont(font);
	fps.setCharacterSize(40);
	fps.setPosition(20, 20);
	fps.setFillColor(sf::Color::White);
	sf::Clock timer;

	createPlayers();
	sf::Event event;

	int cnt = 0;
	timer.restart();
	while (window.isOpen())
	{
		updatePlayers();
		cnt++;
		if (cnt == 200)
		{
			fps.setString(std::to_string(int(cnt / timer.getElapsedTime().asSeconds())));
			timer.restart();
			cnt = 0;
			if (getBoostPosition()) {
				std::cout << boostPosition.x << " : " << boostPosition.y << std::endl;
				//boostsPos.push_back(sf::CircleShape(10));
				//boostsPos.back().setFillColor(sf::Color::Green);
				//boostsPos.back().setOrigin(10, 10);
				//boostsPos.back().setPosition(boostPosition.x, boostPosition.y);
			}
		}
		else if (isF4Pressed())
			setting.TimeStop = !setting.TimeStop;
		else if (isF2Pressed())
		{
			Boost* tmp = new LockRight;
			std::cout << "slow down :";
			Players.back().addBoost(tmp);
		}
		else if (isF3Pressed())
		{
			std::cout << "speed up :";
			Boost* tmp = new LockLeft;
			Players.back().addBoost(tmp);
		}
		else if (isF5Pressed())
		{
			std::cout << "shrink up :";
			Boost* tmp = new Freeze;
			Players.back().addBoost(tmp);
		}
		else if (isF6Pressed())
		{
			EriseAll();
			/*std::cout << "grow up :";
			Boost* tmp = new Blind;
			Players.back().addBoost(tmp);*/
		}
		window.clear(sf::Color::Black);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			return st::mainMenu;

		drawBounds();
		drawPlayers();
		window.draw(fps);
		for (auto& aa : boostsPos)
			window.draw(aa);
		window.display();
		
	}
}


gameBoard::~gameBoard()
{
}
void gameBoard::setBounds(int ymax_, int ymin_, int xmax_, int xmin_, int thicc_)
{
	xmax = xmax_;
	xmin = xmin_;
	ymin = ymin_;
	ymax = ymax_;
	thicc = thicc_;
	bounds[0][0] = sf::Vertex(sf::Vector2f(xmax + thicc, ymin - thicc), sf::Color::White);
	bounds[0][1] = sf::Vertex(sf::Vector2f(xmax, ymin), sf::Color::White);
	bounds[0][2] = sf::Vertex(sf::Vector2f(xmax, ymax), sf::Color::White);
	bounds[0][3] = sf::Vertex(sf::Vector2f(xmax + thicc, ymax + thicc), sf::Color::White);

	bounds[1][0] = sf::Vertex(sf::Vector2f(xmax + thicc, ymax + thicc), sf::Color::White);
	bounds[1][1] = sf::Vertex(sf::Vector2f(xmax, ymax), sf::Color::White);
	bounds[1][2] = sf::Vertex(sf::Vector2f(xmin, ymax), sf::Color::White);
	bounds[1][3] = sf::Vertex(sf::Vector2f(xmin - thicc, ymax + thicc), sf::Color::White);

	bounds[2][0] = sf::Vertex(sf::Vector2f(xmin - thicc, ymax + thicc), sf::Color::White);
	bounds[2][1] = sf::Vertex(sf::Vector2f(xmin, ymax), sf::Color::White);
	bounds[2][2] = sf::Vertex(sf::Vector2f(xmin, ymin), sf::Color::White);
	bounds[2][3] = sf::Vertex(sf::Vector2f(xmin - thicc, ymin - thicc), sf::Color::White);

	bounds[3][0] = sf::Vertex(sf::Vector2f(xmin - thicc, ymin - thicc), sf::Color::White);
	bounds[3][1] = sf::Vertex(sf::Vector2f(xmin, ymin), sf::Color::White);
	bounds[3][2] = sf::Vertex(sf::Vector2f(xmax, ymin), sf::Color::White);
	bounds[3][3] = sf::Vertex(sf::Vector2f(xmax + thicc, ymin - thicc), sf::Color::White);

}

void gameBoard::clearHitbox()
{
	for (auto& x : hitbox)
		for (auto& y : x)
			y = 0;
}

void gameBoard::createPlayers()
{
	Players.clear();
	thicc = 5;
	int i = 0;
	generateMap();
	/*for (auto& x : setting.playersSettings)
	{
		Players.push_back(std::move(Player(allHeadRadious,hitbox, window, x.color, ymax, ymin, xmax, xmin, board)));
		Players.back().setId(i);
		allHeadRadious.push_back(5);
		Players.back().setParams(generteAngle(), 6, 2.5, 100);
		Players.back().setPosition(generatePositions());
		Players.back().setControls(x.left, x.right);
		Players.back().setNick(x.nickname);
		i++;
		Players.back().setGapBounds(40, 300, 500, 1000);

	}*/

	Players.push_back(std::move(Player(allHeadRadious, hitbox, window, sf::Color::Red, ymax, ymin, xmax, xmin, board)));
	Players.back().setId(i);
	allHeadRadious.push_back(5);
	Players.back().setParams(generteAngle(), 6, 2.5, 100);
	Players.back().setPosition(generatePositions());
	Players.back().setControls(sf::Keyboard::Key::S, sf::Keyboard::Key::D);
	Players.back().setNick("sylwow");
	i++;
	Players.back().setGapBounds(40, 300, 500, 1000);

}

bool gameBoard::isF4Pressed()
{
	static bool isPressed = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F4))
	{
		if (!isPressed)
		{
			isPressed = true;
			return true;
		}
		return false;
	}
	else 
	{
		isPressed = false;
		return false;
	}
}
bool gameBoard::isF2Pressed()
{
	static bool isPressed = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
	{
		if (!isPressed)
		{
			isPressed = true;
			return true;
		}
		return false;
	}
	else
	{
		isPressed = false;
		return false;
	}
}
bool gameBoard::isF3Pressed()
{
	static bool isPressed = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F3))
	{
		if (!isPressed)
		{
			isPressed = true;
			return true;
		}
		return false;
	}
	else
	{
		isPressed = false;
		return false;
	}
}
bool gameBoard::isF5Pressed()
{
	static bool isPressed = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F5))
	{
		if (!isPressed)
		{
			isPressed = true;
			return true;
		}
		return false;
	}
	else
	{
		isPressed = false;
		return false;
	}
}
bool gameBoard::isF6Pressed()
{
	static bool isPressed = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F6))
	{
		if (!isPressed)
		{
			isPressed = true;
			return true;
		}
		return false;
	}
	else
	{
		isPressed = false;
		return false;
	}
}
void gameBoard::generateMap()
{
	map.clear();
	int divx = 10;
	int divy = 10;
	int widex = xmax - xmin;
	widex /= divx;
	int widey = ymax - ymin;
	widey /= divy;
	int offx = rand() % widex;
	int offy = rand() % widey;
	divx--;
	divy--;
	for (int i = 1; i < divx; i++)
	{
		for (int j = 1; j < divy; j++)
		{
			map.push_back({ offx + xmin + i * widex, offy + ymin + j * widey });
		}
	}
	divx++;
}
sf::Vector2f gameBoard::generatePositions()
{
	int i = rand() % map.size();
	auto it = map.begin() + i;
	sf::Vector2f tmp;
	tmp.x= it->x;
	tmp.y = it->y;
	map.erase(it);
	return tmp;
}
double gameBoard::generteAngle()
{
	return double(rand() % 360)* 0.0174532925;
}

void gameBoard::EriseId(int id)
{
	Players[id].erise();
	for (int i = 0; i < 1920; i++)
	{
		for (int j = 0; j < 1080; j++)
		{
			if (!hitbox[j][i])
				continue;
			else
			{
				int id_ = hitbox[j][i] >> 28;
				if (id_ == id)
					hitbox[j][i] = 0;
			}
		}
	}
}

void gameBoard::EriseAll()
{
	for (auto& x : Players)
		x.erise();
	for (int i = 0; i < 1920; i++)
	{
		for (int j = 0; j < 1080; j++)
		{
				hitbox[j][i] = 0;
		}
	}
}

bool gameBoard::getBoostPosition()
{
	int X = 1000;// xmin + int(boostR) + rand() % (xmax - xmin - int(boostR));
	int Y = 1000;//ymin + int(boostR) + rand() % (ymax - ymin - int(boostR));
	int lowestRint = 1920;
	int boundRX = 1920 + X;
	int boundRY = 1920 + Y;
	sf::Vector2i point;
	double r = Player::getRScan();
	int R = r > boostR ? round(r) : round(boostR);
	int Ymax = ymax - R;
	int Xmax = xmax - R;
	int Ymin = ymax + R;
	int Xmin = xmax + R;
	double actualR;
	for (int x = X; x < Xmax || x < boundRX; x++)
	{
		for (int y = Y; y < Ymax || y < boundRY; y++)
		{
			if (true)//scan(x, y, R))
			{
				int r_ = round((X - x) * (X - x) + (Y - y) * (Y - y));
				if (r_ < lowestRint)
				{
					lowestRint = r_;
					boundRX = lowestRint + X;
					boundRY = lowestRint + Y;
					boostPosition = { x,y };
				}
			}
			else
				continue;
		}
	}
	/*for (int x = X; x < Xmax || x < lowestRint; x++)
	{
		for (int y = Y; y > Ymin || y > lowestRint; y--)
		{
			if (scan(x, y, R))
			{
				int r_ = round((X - x) * (X - x) + (Y - y) * (Y - y));
				if (r_ < lowestRint)
				{
					lowestRint = r_;
					boostPosition = { x,y };
				}
			}
			else
				continue;
		}
	}
	for (int x = X; x > Xmin || x > lowestRint; x--)
	{
		for (int y = Y; y < Ymax || y < lowestRint; y++)
		{
			if (scan(x, y, R))
			{
				int r_ = round((X - x) * (X - x) + (Y - y) * (Y - y));
				if (r_ < lowestRint)
				{
					lowestRint = r_;
					boostPosition = { x,y };
				}
			}
			else
				continue;
		}
	}
	for (int x = X; x > Xmin || x > lowestRint; x--)
	{
		for (int y = Y; y > Ymin || y > lowestRint; y--)
		{
			if (scan(x, y, R))
			{
				int r_ = round((X - x) * (X - x) + (Y - y) * (Y - y));
				if (r_ < lowestRint)
				{
					lowestRint = r_;
					boostPosition = { x,y };
				}
			}
			else
				continue;
		}
	}*/
	if (lowestRint == 1980)
		return false;
	else
		return true;
}

bool gameBoard::scan(int x, int y, int r)
{
	int begx = x - r;
	if (begx < xmin)
		begx = xmin;
	int begy = y - r;
	if (begy < ymin)
		begy = ymin;
	int endx = x + r;
	if (endx > xmax)
		endx = xmax;
	int endy = y + r;
	if (endy > ymax)
		endy = ymax;
	for (int x = begx; x <= endx; x++)
	{
		for (int y = begy; y <= endy; y++)
		{
			if (hitbox[y][x])
				return false;

		}
	}
	for (auto& b : boostsPos) 
	{
		if (isInCircle(b.getPosition(),sf::Vector2f(x, y), 2 * boostR))
			return false;
	}
	for (auto& b : Players)
	{
		if (isInCircle(b.getPos(),sf::Vector2f(x, y) , 400))//??20
			return false;
	}
	return true;
}
			
