#include "gameBoard.h"



std::array<std::array<long long int, 1920>, 1080> gameBoard::hitbox = { 0 };
gameBoard::gameBoard(sf::RenderWindow& win, Background& back) :
	window(win),
	background(back),
	Players(),
	scoreBoard(window, 30, 500)
{
	this->pause = false;
	setBounds(1075, 5, 1915, 400, 5);
	srand(std::time(0));
	boostR = 40;
	dontSetBoostR = 50;
	minBoostTime = 5;
	maxBoostTime = 10;
	boostTime = getTimeBoost();
	if (!blind.loadFromFile("../boost_icons/blind.png"))
		throw std::exception("boost icon missing");
	if (!boundsShrink.loadFromFile("../boost_icons/bounds.png"))
		throw std::exception("boost icon missing");
	if (!brokenWalls.loadFromFile("../boost_icons/broken_walls.png"))
		throw std::exception("boost icon missing");
	if (!clearAll.loadFromFile("../boost_icons/clean_board.png"))
		throw std::exception("boost icon missing");
	if (!freeze.loadFromFile("../boost_icons/freeze.png"))
		throw std::exception("boost icon missing");
	if (!growUp.loadFromFile("../boost_icons/grow_up.png"))
		throw std::exception("boost icon missing");
	if (!hydra.loadFromFile("../boost_icons/hydra.png"))
		throw std::exception("boost icon missing");
	if (!immortal.loadFromFile("../boost_icons/immortal.png"))
		throw std::exception("boost icon missing");
	if (!longerGaps.loadFromFile("../boost_icons/longer_gaps.png"))
		throw std::exception("boost icon missing");
	if (!moreOftenHoles.loadFromFile("../boost_icons/more_often_holes.png"))
		throw std::exception("boost icon missing");
	if (!lockLeft.loadFromFile("../boost_icons/only_left2.png"))
		throw std::exception("boost icon missing");
	if (!shrink.loadFromFile("../boost_icons/shrink.png"))
		throw std::exception("boost icon missing");
	if (!slowDown.loadFromFile("../boost_icons/slow_down.png"))
		throw std::exception("boost icon missing");
	if (!speedUp.loadFromFile("../boost_icons/speed_up.png"))
		throw std::exception("boost icon missing");
	if (!stop.loadFromFile("../boost_icons/stop_freeze.png"))
		throw std::exception("boost icon missing");
	if (!switchControls.loadFromFile("../boost_icons/switch_controls.png"))
		throw std::exception("boost icon missing");
	if (!switchHeads.loadFromFile("../boost_icons/switch_head.png"))
		throw std::exception("boost icon missing");
	if (!font.loadFromFile("../Font/kenvector_future_thin.ttf"))
		throw std::exception("font file missing");

	startUpText.setFont(font);
	startUpText.setCharacterSize(80);
	startUpText.setFillColor(sf::Color::White);
	startUpText.setPosition(xmin + (xmax - xmin) / 2, ymin + (ymax - ymin) / 2 - 100);

	Winner.setFont(font);
	Winner.setCharacterSize(80);
	Winner.setFillColor(sf::Color::White);
	Winner.setPosition(xmin + (xmax - xmin) / 2, ymin + (ymax - ymin) / 2 - 100);

}

st gameBoard::update()
{

	sf::Text fps;
	fps.setFont(font);
	fps.setCharacterSize(40);
	fps.setPosition(20, 20);
	fps.setFillColor(sf::Color::White);

	sf::Clock timer;
	sf::Clock boostTImer;

	if (!setting.pause)
	{
		clearHitbox();
		clearBoosts();
		createPlayers();
		scoreBoard.setPosition(20, 400, Players, font);
		AllRounds = setting.rounds;
		rounds = AllRounds;
	}
	int cnt = 0;
	sf::Event event;

	while (rounds)
	{
		timer.restart();
		boostTImer.restart();
		if (!setting.pause)
		{
			end = false;
			start = true;
			poolPoints = 1;
			setting.TimeStop = true;
			spacePressed = false;
			sec = 3;
			startUpText.setString("press space to start");
			startUpText.setOrigin(startUpText.getGlobalBounds().width / 2, startUpText.getGlobalBounds().height / 2);
		}
		while (window.isOpen())
		{
			if (start)
			{
				if (!spacePressed)
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
					{
						spacePressed = true;
						startUpText.setString("round " + std::to_string(AllRounds - rounds + 1));
						startUpText.setOrigin(startUpText.getGlobalBounds().width / 2, startUpText.getGlobalBounds().height / 2);
						boostTImer.restart();
					}
				}
				else if (boostTImer.getElapsedTime().asSeconds() > 1)
				{
					startUpText.setString(std::to_string(sec));
					startUpText.setOrigin(startUpText.getGlobalBounds().width / 2, startUpText.getGlobalBounds().height / 2);
					boostTImer.restart();
					if (sec == 0)
					{
						start = false;
						setting.TimeStop = false;
						continue;
					}
					sec--;
				}

			}
			else if (end)
			{
				if (boostTImer.getElapsedTime().asSeconds() > 3)
				{
					rounds--;
					restart();
					break;
				}
			}
			if (cnt == 200)
			{
				fps.setString(std::to_string(int(cnt / timer.getElapsedTime().asSeconds())));
				timer.restart();
				cnt = 0;
			}
			if (poolPoints == Players.size())
			{
				poolPoints++;
				for (auto& winner : Players)
				{
					if (!winner.getState())
					{
						end = true;
						winner.die();
						winner.addPoints(poolPoints);
						scoreBoard.updateScore(winner.getId(), winner);
						Winner.setString("Round winner :" + winner.getNickname());
						Winner.setOrigin(Winner.getGlobalBounds().width / 2, Winner.getGlobalBounds().height / 2);
						boostTImer.restart();
					}
				}

			}
			updatePlayers();
			scoreBoard.update();
			checkBoostsColission();
			cnt++;
			if (!start && !end && boostTImer.getElapsedTime().asSeconds() > boostTime)
			{
				boostTImer.restart();
				if (!setting.TimeStop)
				{
					boostTime = getTimeBoost();
					if (boostsOnBoard.size() < 21) {
						drawOnHitTmp();
						if (getBoostPosition())
						{
							markBoostPosOnHit(boostPosition);
							getRandomBoost();
							//dodaj boost;
						}
						clearOnHitTmp();
					}
				}
				//else nie ma miejsca
			}
			window.clear(sf::Color::Black);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				setting.pause = true;
				setting.TimeStop = true;
				return st::pause;
			}
			else if (isF6Pressed())
				setting.TimeStop = !setting.TimeStop;

			//background.draw();
			drawBounds();
			drawPlayers();
			window.draw(fps);
			for (auto& aa : boostsOnBoard)
				window.draw(aa);
			if (start)
				window.draw(startUpText);
			else if (end)
				window.draw(Winner);
			scoreBoard.draw();
			window.display();
			if (setting.pause)
			{
				setting.pause = false;
				if(!start)
					setting.TimeStop = false;
			}
		}
	}
	//podsumowanie ranking itp
	return st::mainMenu;
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
		Players.push_back(std::move(Player(allHeadRadious, hitbox, window, x.color, ymax, ymin, xmax, xmin)));
		Players.back().setId(i);
		allHeadRadious.push_back(5);
		Players.back().setParams(generteAngle(), 6, 2.5, 100);
		Players.back().setPosition(generatePositions());
		Players.back().setControls(x.left, x.right);
		Players.back().setNick(x.nickname);
		i++;
		Players.back().setGapBounds(40, 300, 500, 1000);

	}

	/*Players.push_back(std::move(Player(allHeadRadious, hitbox, window, sf::Color::Red, ymax, ymin, xmax, xmin)));
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
}
sf::Vector2f gameBoard::generatePositions()
{
	int i = rand() % map.size();
	auto it = map.begin() + i;
	sf::Vector2f tmp;
	tmp.x = it->x;
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
	int X = xmin + int(boostR) + rand() % (xmax - xmin - int(boostR));
	int Y = ymin + int(boostR) + rand() % (ymax - ymin - int(boostR));
	int lowestRint = 2500;
	int lowestRintPow = 2500 * 2500;;
	int boundRX = 1920 + X;
	int boundRY = 1920 + Y;
	sf::Vector2i point;
	int R = boostR;
	int Ymax = ymax - R;
	int Xmax = xmax - R;
	int Ymin = ymin + R;
	int Xmin = xmin + R;
	double actualR;
	for (int x = X; x < Xmax && x < boundRX; x++)
	{
		for (int y = Y; y < Ymax && y < boundRY; y++)
		{
			if (!hitbox[y][x])//scan(x, y, R))
			{
				int r_ = round((X - x) * (X - x) + (Y - y) * (Y - y));
				if (r_ < lowestRintPow)
				{
					lowestRintPow = r_;
					lowestRint = round(sqrt(r_));
					boundRX = lowestRint + X;
					boundRY = lowestRint + Y;
					boostPosition = { x,y };
				}
			}
			else
				continue;
		}
	}
	boundRX = lowestRint + X;
	boundRY = Y - lowestRint;
	for (int x = X; x < Xmax && x < boundRX; x++)
	{
		for (int y = Y; y > Ymin && y > boundRY; y--)
		{
			if (!hitbox[y][x])//scan(x, y, R))
			{
				int r_ = round((X - x) * (X - x) + (Y - y) * (Y - y));
				if (r_ < lowestRintPow)
				{
					lowestRintPow = r_;
					lowestRint = round(sqrt(r_));
					boundRX = lowestRint + X;
					boundRY = Y - lowestRint;
					boostPosition = { x,y };
				}
			}
			else
				continue;
		}
	}
	boundRX = X - lowestRint;
	boundRY = lowestRint + Y;
	for (int x = X; x > Xmin && x > boundRX; x--)
	{
		for (int y = Y; y < Ymax && y < boundRY; y++)
		{
			if (!hitbox[y][x])//scan(x, y, R))
			{
				int r_ = round((X - x) * (X - x) + (Y - y) * (Y - y));
				if (r_ < lowestRintPow)
				{
					lowestRintPow = r_;
					lowestRint = round(sqrt(r_));
					boundRX = X - lowestRint;
					boundRY = lowestRint + Y;
					boostPosition = { x,y };
				}
			}
			else
				continue;
		}
	}
	boundRX = X - lowestRint;
	boundRY = Y - lowestRint;
	for (int x = X; x > Xmin && x > boundRX; x--)
	{
		for (int y = Y; y > Ymin && y > boundRY; y--)
		{
			if (!hitbox[y][x])//scan(x, y, R))
			{
				int r_ = round((X - x) * (X - x) + (Y - y) * (Y - y));
				if (r_ < lowestRintPow)
				{
					lowestRintPow = r_;
					lowestRint = round(sqrt(r_));
					boundRX = X - lowestRint;
					boundRY = Y - lowestRint;
					boostPosition = { x,y };
				}
			}
			else
				continue;
		}
	}
	if (lowestRint == 2500)
		return false;
	else
		return true;
}

void gameBoard::drawOnHitTmp()
{
	for (auto& x : Players) {
		sf::Vector2f position = x.getPos();

		int begx = round(position.x - dontSetBoostR);
		if (begx < xmin)
			begx = xmin;
		int begy = round(position.y - dontSetBoostR);
		if (begy < ymin)
			begy = ymin;
		int endx = round(position.x + dontSetBoostR);
		if (endx > xmax)
			endx = xmax;
		int endy = round(position.y + dontSetBoostR);
		if (endy > ymax)
			endy = ymax;

		long long int info;
		info = long long int(1) << 63;

		for (int x = begx; x <= endx; x++)
		{
			for (int y = begy; y <= endy; y++)
			{
				if (hitbox[y][x])
					continue;
				else
				{
					if (((x - position.x) * (x - position.x) + (y - position.y) * (y - position.y)) < dontSetBoostR * dontSetBoostR)
					{
						hitbox[y][x] = info;
					}
				}
			}
		}
	}
}

void gameBoard::clearOnHitTmp()
{
	for (int x = 0; x < 1920; x++)
	{
		for (int y = 0; y < 1080; y++)
		{
			if (hitbox[y][x] >> 63)
				hitbox[y][x] = 0;
		}
	}
}

void gameBoard::getRandomBoost()
{
	int N = 9;
	int choice = rand() % N;
	boostsOnBoard.push_back(BoostOnBoard());
	Boost* wsk;
	switch (choice)
	{
	case 0:
		wsk = new GrowUp;
		boostsOnBoard.back().setTexture(growUp);
		break;
	case 1:
		wsk = new Shrink;
		boostsOnBoard.back().setTexture(shrink);
		break;
	case 2:
		wsk = new SpeedUp;
		boostsOnBoard.back().setTexture(speedUp);
		break;
	case 3:
		wsk = new SlowDown;
		boostsOnBoard.back().setTexture(slowDown);
		break;
	case 4:
		wsk = new LockLeft;
		boostsOnBoard.back().setTexture(lockLeft);
		break;
	case 5:
		wsk = new LockRight;
		boostsOnBoard.back().setTexture(lockRight);
		break;
	case 6:
		wsk = new Freeze;
		boostsOnBoard.back().setTexture(freeze);
		break;
	case 7:
		wsk = new SwitchControls;
		boostsOnBoard.back().setTexture(switchControls);
		break;
	case 8:
		wsk = new Blind;
		boostsOnBoard.back().setTexture(blind);
		break;
	default:
		wsk = new Blind;
		boostsOnBoard.back().setTexture(blind);
		break;
	}
	boostsOnBoard.back().setBoost(wsk);
	boostsOnBoard.back().setScale(0.1, 0.1);
	boostsOnBoard.back().setOrigin(32, 32);
	boostsOnBoard.back().setPosition(boostPosition.x, boostPosition.y);
}

void gameBoard::markBoostPosOnHit(sf::Vector2i boostPosition)
{
	int begx = round(boostPosition.x - boostR);
	if (begx < xmin)
		begx = xmin;
	int begy = round(boostPosition.y - boostR);
	if (begy < ymin)
		begy = ymin;
	int endx = round(boostPosition.x + boostR);
	if (endx > xmax)
		endx = xmax;
	int endy = round(boostPosition.y + boostR);
	if (endy > ymax)
		endy = ymax;

	long long int info;
	info = long long int(1) << 62;

	for (int x = begx; x <= endx; x++)
	{
		for (int y = begy; y <= endy; y++)
		{
			if (hitbox[y][x])
				continue;
			else
			{
				if (((x - boostPosition.x) * (x - boostPosition.x) + (y - boostPosition.y) * (y - boostPosition.y)) < boostR * boostR)
				{
					hitbox[y][x] = info;
				}
			}
		}
	}
}
void gameBoard::clearBoostPosOnHit(sf::Vector2f boostPosition)
{
	int begx = round(boostPosition.x - boostR);
	if (begx < xmin)
		begx = xmin;
	int begy = round(boostPosition.y - boostR);
	if (begy < ymin)
		begy = ymin;
	int endx = round(boostPosition.x + boostR);
	if (endx > xmax)
		endx = xmax;
	int endy = round(boostPosition.y + boostR);
	if (endy > ymax)
		endy = ymax;

	long long int info;
	info = long long int(1) << 62;

	for (int x = begx; x <= endx; x++)
	{
		for (int y = begy; y <= endy; y++)
		{
			if ((hitbox[y][x] >> 62) & 1)
				hitbox[y][x] = 0;
		}
	}
}

void gameBoard::checkBoostsColission()
{
	std::vector<BoostOnBoard>::iterator it;
	bool found;
	for (auto& player : Players)
	{
		found = false;
		sf::Vector2f playertPos = player.getPos();
		for (it = boostsOnBoard.begin(); it != boostsOnBoard.end(); it++)
		{
			sf::Vector2f boostPos = it->getPosition();
			if (((double(playertPos.x) - boostPos.x) * (double(playertPos.x) - boostPos.x) + (double(playertPos.y) - boostPos.y) * (double(playertPos.y) - boostPos.y)) < (player.getRadious() + boostR) * (player.getRadious() + boostR))
			{
				found = true;
				player.addBoost(it->getBoost());
				clearBoostPosOnHit(it->getPosition());
				break;
			}
		}
		if (found)
			boostsOnBoard.erase(it);
	}
}

void gameBoard::clearBoosts()
{
	for (auto& x : boostsOnBoard)
	{
		delete x.getBoost();
	}
	boostsOnBoard.clear();
}

void gameBoard::restart()
{
	generateMap();
	boostTime = getTimeBoost();
	clearHitbox();
	clearBoosts();
	for (auto& player : Players)
	{
		player.setParams(generteAngle(), 6, 2.5, 100);
		player.setPosition(generatePositions());
		player.reset();
	}
	/*Players.back().setParams(generteAngle(), 6, 2.5, 100);
	Players.back().setPosition(generatePositions());
	Players.back().reset();
	*/
}


