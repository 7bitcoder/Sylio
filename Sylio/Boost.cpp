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


bool Boost::check(Player& player)
{
	if (setting.TimeStop || player.freeze)
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
	player.hiddenVelocity *= multVel;
	if (player.hiddenVelocity < limits.minVel)
		player.velocity = limits.minVel;
	else if (player.hiddenVelocity > limits.maxVel)
		player.velocity = limits.maxVel;
	else
		player.velocity = player.hiddenVelocity;
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
	player.hiddenVelocity *= multVel;
	if (player.hiddenVelocity < limits.minVel)
		player.velocity = limits.minVel;
	else if (player.hiddenVelocity > limits.maxVel)
		player.velocity = limits.maxVel;
	else
		player.velocity = player.hiddenVelocity;
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
	player.hiddenHeadR *= multSize;
	if (player.hiddenHeadR < limits.minRadious)
		player.setWaitingR(limits.minRadious);
	else if (player.hiddenHeadR > limits.maxRadious)
		player.setWaitingR(limits.maxRadious);
	else
		player.setWaitingR(player.hiddenHeadR);
}

void GrowUp::clearBoost(Player& player)
{
	player.hiddenHeadR /= multSize;
	if (player.hiddenHeadR < limits.minRadious)
		player.setWaitingR(limits.minRadious);
	else if (player.hiddenHeadR > limits.maxRadious)
		player.setWaitingR(limits.maxRadious);
	else
		player.setWaitingR(player.hiddenHeadR);
}

void Shrink::setBoost(Player& player)
{
	player.hiddenHeadR *= multSize;
	if (player.hiddenHeadR < limits.minRadious)
		player.setWaitingR(limits.minRadious);
	else if (player.hiddenHeadR > limits.maxRadious)
		player.setWaitingR(limits.maxRadious);
	else
		player.setWaitingR(player.hiddenHeadR);
}

void Shrink::clearBoost(Player& player)
{
	player.hiddenHeadR /= multSize;
	if (player.hiddenHeadR < limits.minRadious)
		player.setWaitingR(limits.minRadious);
	else if (player.hiddenHeadR > limits.maxRadious)
		player.setWaitingR(limits.maxRadious);
	else
		player.setWaitingR(player.hiddenHeadR);

}

void LockLeft::setBoost(Player& player)
{
	player.lockLeft = true;
}

void LockLeft::clearBoost(Player& player)
{
	player.lockLeft = false;
}

void LockRight::setBoost(Player& player)
{
	player.lockRight = true;
}

void LockRight::clearBoost(Player& player)
{
	player.lockRight = false;
}

void Freeze::setBoost(Player& player)
{
	player.freeze = true;
}

void Freeze::clearBoost(Player& player)
{
	player.freeze = false;
}

bool Freeze::check(Player& player)
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

void SwitchControls::setBoost(Player& player)
{
	std::swap(player.left, player.right);
}

void SwitchControls::clearBoost(Player& player)
{
	std::swap(player.left, player.right);
}

void Blind::setBoost(Player& player)
{
	player.visible = false;
}

void Blind::clearBoost(Player& player)
{
	player.visible = true;
}
