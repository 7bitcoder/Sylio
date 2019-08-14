#include "ScoreBoard.h"


void ScoreBoard::update()
{
	if (updating)
	{
		move(main);
		checkColide();
		bool moving = false;
		for (int i = 0; i < dates.size(); i++)
		{
			if (dates[i].moving && i != main)
			{
				moving = true;
				move(i);
			}
		}
		if (!moving && !dates[main].moving)
			updating = false;
	}
	else if (!que.empty())
	{
		main = que.front();
		que.pop();
		updating = true;
		dates[main].main = true;
		dates[main].moving = true;
		dates[main].timer.restart();
	}
}

void ScoreBoard::updateScore(int id, Player & players)
{

	dates[id].score = players.getPoints();
	dates[id].text.setString(dates[id].nickname + std::to_string(dates[id].score));
	dates[id].dest = findPosition(id);
	que.push(id);
}

void ScoreBoard::draw()
{
	if (main != -1)
		window.draw(dates[main].text);
	for (int i = 0; i < dates.size(); i++)
	{
		if (i != main)
			window.draw(dates[i].text);
	}
}

void ScoreBoard::move(int id)
{
	float ymove = dates[id].timer.getElapsedTime().asSeconds() * vel;
	dates[id].timer.restart();
	if (dates[id].up)
	{
		dates[id].text.move(0, -ymove);
		if (dates[id].text.getPosition().y < positions[dates[id].position - 1])
		{
			dates[id].position--;
			if (dates[id].position == dates[id].dest)
			{
				dates[id].text.setPosition(posx, positions[dates[id].position]);
				dates[id].moving = false;
				if (dates[id].main)
				{
					dates[id].main = false;
					main = -1;
				}
			}
		}
	}
	else
	{
		dates[id].text.move(0, ymove);
		if (dates[id].text.getPosition().y > positions[dates[id].position + 1])
		{
			dates[id].position++;
			if (dates[id].position == dates[id].dest)
			{
				dates[id].text.setPosition(posx, positions[dates[id].position]);
				dates[id].moving = false;
				if (dates[id].main)
					dates[id].main = false;
			}
		}
	}
}

void ScoreBoard::checkColide()
{
	if (positions[dates[main].position] != main)
	{
		int id = positions[dates[main].position];
		dates[id].moving = true;
		dates[id].up = !dates[main].up;
		dates[id].timer.restart();
		if (dates[id].up)
		{
			dates[id].dest = dates[id].position - 1;
			std::swap(positions[dates[main].position], positions[dates[main].position - 1]);
		}
		else
		{
			dates[id].dest = dates[id].position + 1;
			std::swap(positions[dates[main].position], positions[dates[main].position + 1]);
		}
	}
}

void ScoreBoard::setPosition(int x, int y, std::vector<Player>& players)
{
	updating = false;
	posx = x;
	for (auto& player : players)
	{
		dates.push_back(std::move(data{ 0,player.getNickname() + " ",false,0,false,0, true, }));
		dates.back().text.setFillColor(player.getColor());
		dates.back().text.setCharacterSize(charSize);
		dates.back().text.setString(dates.back().nickname + std::to_string(dates.back().score));
	}
	for (int i = 0; i < dates.size(); i++)
	{
		positions.push_back(y + i * (charSize) * 1.2);
		dates[i].text.setPosition(x, positions.back());
		dates[i].position = i;
		rank.push_back(i);
	}
}
int ScoreBoard::findPosition(int id)
{
	int score = dates[id].score;
	for (int i = id; i >= 0; i--)
	{
		if (i != id)
			if (dates[i].score <= score)
			{
				dates[id].dest = dates[i].position;
				dates[id].up = true;
			}
	}
	return 0;
}

ScoreBoard::ScoreBoard( sf::RenderWindow & win, int size, float vel_) :
	window(win)
{
	vel = vel_;
	updating = false;
	charSize = size;
}

ScoreBoard::~ScoreBoard()
{
}
