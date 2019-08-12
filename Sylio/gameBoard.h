#pragma once
#include "Settings.h"
#include "Boost.h"
#include "Player.h"

extern Settings setting;
class gameBoard
{
private:
	static std::array<std::array<long long int, 1920>, 1080> hitbox;
	int xmax;
	int xmin;
	int ymin;
	int ymax;
	int thicc;
	double dontSetBoostR;
	sf::Vector2i boostPosition;
	double boostR;
	std::vector<sf::Vector2i> map;
	sf::Vertex bounds[4][4];
	std::vector<Player> Players;
	std::vector<sf::CircleShape> boostsPos;
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
public:
	gameBoard(sf::RenderWindow& win);
	st update();
	~gameBoard();
	void setBounds(int ymax_, int ymin_, int xmax_, int xmin_, int thicc);
	void clearHitbox();
	void createPlayers();
	bool isF4Pressed();
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
	void markBoostPosOnHit(sf::Vector2i boostPosition);
	void clearBoostPosOnHit(sf::Vector2i boostPosition);
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
				player.update();
				player.checkBoosts();
				player.checkBounds();
			}
		}
	}
	void drawPlayers()
	{
		for (auto& player : Players)
			player.draw();
	}

};

