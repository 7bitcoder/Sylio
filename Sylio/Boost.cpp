#include "Boost.h"
#include "Player.h"

struct limitations
{
	float maxVel = 500;
	float minVel = 50;
} limits;

class Player;
Boost::Boost()
{
}


Boost::~Boost()
{
}

void SpeedUp::setBoost(Player& player)
{
	player.velocity *= multVel;
	if (player.velocity > limits.maxVel)
		player.velocity = limits.maxVel;
}

void SpeedUp::clearBoost(Player& player)
{
	player.velocity /= multVel;
	if (player.velocity < limits.minVel)
		player.velocity = limits.minVel;
}

bool SpeedUp::check()
{
	return clock.getElapsedTime().asSeconds() > duration;
}

