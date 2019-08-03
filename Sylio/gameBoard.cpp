#include "gameBoard.h"


std::array<std::array<int, 1920>, 1080> gameBoard::hitbox = { 0 };
gameBoard::gameBoard(sf::RenderWindow& win) :window(win)
{
	setBounds(1075, 5, 1915, 300, 5);
	board.create(window.getSize().x, window.getSize().y);
	board.clear(sf::Color::Black);
	srand(std::time(0));
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
		}
		else if (isF4Pressed())
			setting.TimeStop = !setting.TimeStop;
		else if (isF2Pressed())
		{
			Boost* tmp = new SlowDown;
			std::cout << "slow down :";
			Players.back().addBoost(tmp);
		}
		else if (isF3Pressed())
		{
			std::cout << "speed up :";
			Boost* tmp = new SpeedUp;
			Players.back().addBoost(tmp);
		}
		else if (isF5Pressed())
		{
			std::cout << "shrink up :";
			Boost* tmp = new Shrink;
			Players.back().addBoost(tmp);
		}
		else if (isF6Pressed())
		{
			std::cout << "grow up :";
			Boost* tmp = new GrowUp;
			Players.back().addBoost(tmp);
		}
		window.clear(sf::Color::Black);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			return st::mainMenu;

		drawBounds();
		drawPlayers();
		window.draw(fps);
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
	for (auto& x : setting.playersSettings)
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

	}

	/*Players.push_back(std::move(Player(allHeadRadious, hitbox, window, sf::Color::Red, ymax, ymin, xmax, xmin, board)));
	Players.back().setId(i);
	allHeadRadious.push_back(5);
	Players.back().setParams(generteAngle(), 6, 2.5, 100);
	Players.back().setPosition(generatePositions());
	Players.back().setControls(sf::Keyboard::Key::S, sf::Keyboard::Key::D);
	Players.back().setNick("sylwow");
	i++;
	Players.back().setGapBounds(40, 300, 500, 1000);
*/
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
sf::Vector2i gameBoard::generatePositions()
{
	int i = rand() % map.size();
	auto it = map.begin() + i;
	sf::Vector2i tmp = *it;
	map.erase(it);
	return tmp;
}
double gameBoard::generteAngle()
{
	return double(rand() % 360)* 0.0174532925;
}