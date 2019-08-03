#pragma once
#include <SFML/Window.hpp>
class Player;
class Boost
{
protected:
	float duration;
	sf::Clock clock;
	sf::Vector2i position;
public:
	Boost();
	virtual void setBoost(Player& player) = 0;
	virtual void clearBoost(Player& player) = 0;
	virtual bool check() = 0;
	virtual ~Boost();
};

class SpeedUp: public Boost
{
private:
	float multVel;
public:
	SpeedUp(sf::Vector2i pos) { duration = 5; clock.restart(); position = pos; multVel = 1.2; }
	virtual void setBoost(Player& player);
	virtual void clearBoost(Player& player);
	virtual bool check();
	virtual ~SpeedUp();
};
