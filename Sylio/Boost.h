#pragma once
#include <SFML/Window.hpp>
class Player;
class Boost
{
protected:
	float duration;
	bool timeFlag = false;
	sf::Clock clock;
public:
	Boost();
	virtual void setBoost(Player& player) {};
	virtual void clearBoost(Player& player) {};
	virtual bool check(Player& player);
	virtual bool stack() { return false; };
	virtual float getDuration() { return duration; }
	virtual void addDuration(float dur) { duration += dur; }
	virtual ~Boost();
};

class SpeedUp : public Boost
{
private:
	float multVel;
public:
	SpeedUp(float dur = 5) { duration = dur; clock.restart(); multVel = 1.2; }
	virtual void setBoost(Player& player);
	virtual void clearBoost(Player& player);
	virtual ~SpeedUp() {};
};
class SlowDown : public Boost
{
private:
	float multVel;
public:
	SlowDown(float dur = 5) { duration = dur; clock.restart(); multVel = 0.8; }
	virtual void setBoost(Player& player);
	virtual void clearBoost(Player& player);
	virtual ~SlowDown() {};
};
class GrowUp : public Boost
{
private:
	float multSize;
public:
	GrowUp(float dur = 5) { duration = dur; clock.restart(); multSize = 3; }
	virtual void setBoost(Player& player);
	virtual void clearBoost(Player& player);
	virtual ~GrowUp() {};
};
class Shrink : public Boost
{
private:
	float multSize;
public:
	Shrink(float dur = 5) { duration = dur; clock.restart(); multSize = 0.2; }
	virtual void setBoost(Player& player);
	virtual void clearBoost(Player& player);
	virtual ~Shrink() {};
};
class LockLeft : public Boost
{
private:
public:
	LockLeft(float dur = 5) { duration = dur; clock.restart(); }
	virtual void setBoost(Player& player);
	virtual void clearBoost(Player& player);
	virtual bool stack() { return true; }
	virtual ~LockLeft() {};
};
class LockRight : public Boost
{
private:
public:
	LockRight(float dur = 5) { duration = dur; clock.restart(); }
	virtual void setBoost(Player& player);
	virtual void clearBoost(Player& player);
	virtual bool stack() { return true; }
	virtual ~LockRight() {};
};
class Freeze : public Boost
{
private:
public:
	Freeze(float dur = 5) { duration = dur; clock.restart(); }
	virtual void setBoost(Player& player);
	virtual void clearBoost(Player& player);
	virtual bool check(Player& player);
	virtual bool stack() { return true; }
	virtual ~Freeze() {};
};
class SwitchControls : public Boost
{
private:
public:
	SwitchControls(float dur = 5) { duration = dur; clock.restart(); }
	virtual void setBoost(Player& player);
	virtual void clearBoost(Player& player);
	virtual bool stack() { return true; }
	virtual ~SwitchControls() {};
};
class Blind : public Boost
{
private:
public:
	Blind(float dur = 5) { duration = dur; clock.restart(); }
	virtual void setBoost(Player& player);
	virtual void clearBoost(Player& player);
	virtual bool stack() { return true; }
	virtual ~Blind() {};
};
