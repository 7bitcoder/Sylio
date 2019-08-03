#include "Boost.h"
#include "Player.h"
#include "Settings.h"

extern Settings setting;

struct limitations
{
	double maxVel = 500;
	double minVel = 50;
	double minRadious = 5;
	double maxRadious = 30;
} limits;

class Player;
Boost::Boost()
{
}


bool Boost::check()
{
	if (setting.TimeStop)
	{
		if (!timeFlag)
		{
			timeFlag = true;
			duration -= clock.getElapsedTime().asSeconds();
		}
		clock.restart();
		return false;
	}
	else
		timeFlag = false;
	return clock.getElapsedTime().asSeconds() > duration;
}

Boost::~Boost()
{
}

void SpeedUp::setBoost(Player& player)
{
	std::cout << player.velocity << " to ";
	player.hiddenVelocity *= multVel;
	if (player.hiddenVelocity < limits.minVel)
		player.velocity = limits.minVel;
	else if (player.hiddenVelocity > limits.maxVel)
		player.velocity = limits.maxVel;
	else
		player.velocity = player.hiddenVelocity;
	std::cout << player.velocity << std::endl;
}

void SpeedUp::clearBoost(Player& player)
{
	player.hiddenVelocity /= multVel;
	if (player.hiddenVelocity < limits.minVel)
		player.velocity = limits.minVel;
	else if (player.hiddenVelocity > limits.maxVel)
		player.velocity = limits.maxVel;
	else
		player.velocity = player.hiddenVelocity;
}


void SlowDown::setBoost(Player& player)
{
	std::cout << player.velocity << " to ";
	player.hiddenVelocity *= multVel;
	if (player.hiddenVelocity < limits.minVel)
		player.velocity = limits.minVel;
	else if(player.hiddenVelocity > limits.maxVel)
		player.velocity = limits.maxVel;
	else
		player.velocity = player.hiddenVelocity;
	std::cout << player.velocity << std::endl;
}

void SlowDown::clearBoost(Player& player)
{
	player.hiddenVelocity /= multVel;
	if (player.hiddenVelocity > limits.maxVel)
		player.velocity = limits.maxVel;
	else if (player.hiddenVelocity < limits.minVel)
		player.velocity = limits.minVel;
	else
		player.velocity = player.hiddenVelocity;
}

void GrowUp::setBoost(Player& player)
{
	std::cout << player.headR << " to ";
	player.hiddenHeadR *= multSize;
	if (player.hiddenHeadR < limits.minRadious)
		player.changeRadious(limits.minRadious);
	else if (player.hiddenHeadR > limits.maxRadious)
		player.changeRadious(limits.maxRadious);
	else
		player.changeRadious(player.hiddenHeadR);
	std::cout << player.headR << std::endl;
}

void GrowUp::clearBoost(Player& player)
{
	player.hiddenHeadR /= multSize;
	if (player.hiddenHeadR < limits.minRadious)
		player.changeRadious(limits.minRadious);
	else if (player.hiddenHeadR > limits.maxRadious)
		player.changeRadious(limits.maxRadious);
	else
		player.changeRadious(player.hiddenHeadR);
}

void Shrink::setBoost(Player& player)
{
	std::cout << player.headR << " to ";
	player.hiddenHeadR *= multSize;
	if (player.hiddenHeadR < limits.minRadious)
		player.changeRadious(limits.minRadious);
	else if (player.hiddenHeadR > limits.maxRadious)
		player.changeRadious(limits.maxRadious);
	else
		player.changeRadious(player.hiddenHeadR);
	std::cout << player.headR << std::endl;
}

void Shrink::clearBoost(Player& player)
{
	player.hiddenHeadR /= multSize;
	if (player.hiddenHeadR < limits.minRadious)
		player.changeRadious(limits.minRadious);
	else if (player.hiddenHeadR > limits.maxRadious)
		player.changeRadious(limits.maxRadious);
	else
		player.changeRadious(player.hiddenHeadR);

}
