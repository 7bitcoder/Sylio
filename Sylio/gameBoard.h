#pragma once
#include "Settings.h"
#include "Boost.h"
#include "Player.h"
#include "BoostOnBoard.h"
#include "Background.h"
#include "ScoreBoard.h"

extern Settings setting;
class gameBoard
{
private:
	static std::array<std::array<long long int, 1920>, 1080> hitbox;
	Background& background;
	int xmax;
	int xmin;
	int ymin;
	int ymax;
	int thicc;
	int poolPoints;
	int minBoostTime;
	int maxBoostTime;
	double boostTime;
	double dontSetBoostR;//normalbooostR*2
	sf::Vector2i boostPosition;
	double boostR;
	std::vector<sf::Vector2i> map;
	sf::Vertex bounds[4][4];
	std::vector<Player> Players;
	std::vector<BoostOnBoard> boostsOnBoard;
	std::vector<double> allHeadRadious;
	sf::RenderWindow& window;
	sf::Texture blind;
	sf::Texture boundsShrink;
	sf::Texture brokenWalls;
	sf::Texture clearAll;
	sf::Texture freeze;
	sf::Texture growUp;
	sf::Texture hydra;
	sf::Texture immortal;
	sf::Texture longerGaps;
	sf::Texture moreOftenHoles;
	sf::Texture lockLeft;
	sf::Texture lockRight;
	sf::Texture shrink;
	sf::Texture slowDown;
	sf::Texture speedUp;
	sf::Texture stop;
	sf::Texture switchControls;
	sf::Texture switchHeads;
	ScoreBoard scoreBoard;
public:
	gameBoard(sf::RenderWindow& win, Background & back);
	st update();
	~gameBoard();
	void setBounds(int ymax_, int ymin_, int xmax_, int xmin_, int thicc);
	void clearHitbox();
	void createPlayers();
	bool isF2Pressed();
	bool isF3Pressed();
	bool isF5Pressed();
	bool isF6Pressed();
	void generateMap();
	sf::Vector2f generatePositions();
	double generteAngle();
	void EriseId(int id);
	void EriseAll();
	bool getBoostPosition();
	void drawOnHitTmp();
	void clearOnHitTmp();
	void getRandomBoost();
	void markBoostPosOnHit(sf::Vector2i boostPosition);
	void clearBoostPosOnHit(sf::Vector2f boostPosition);
	void checkBoostsColission();
	float getTimeBoost() { return minBoostTime + rand() % (maxBoostTime - minBoostTime); }
	void drawBounds() {
		window.draw(bounds[0], 4, sf::Quads);
		window.draw(bounds[1], 4, sf::Quads);
		window.draw(bounds[2], 4, sf::Quads);
		window.draw(bounds[3], 4, sf::Quads);
	}
	void updatePlayers()
	{
		for (auto& player : Players)
		{
			if (!player.getState())
			{
				if(player.update() || player.checkBounds())
				{
					player.addPoints(poolPoints);
					poolPoints++;
					scoreBoard.updateScore(player.getId(), player);
				}
				else
					player.checkBoosts();
			}
		}
	}
	void drawPlayers()
	{
		for (auto& player : Players)
			player.draw();
	}
	void clearBoosts();
	void restart();
};

