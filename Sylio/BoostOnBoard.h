#pragma once
#include <SFML/Graphics.hpp>
#include "Boost.h"
class BoostOnBoard: public sf::Sprite
{
private:
	Boost* boost;

public:
	void setBoost(Boost* b) { boost = b; }
	Boost* getBoost() { boost->resetClock(); return boost; }
	BoostOnBoard();
	~BoostOnBoard();
};

