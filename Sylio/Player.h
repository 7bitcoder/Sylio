#pragma once
#include <SFML/Graphics.hpp>
class Player
{
private:
	sf::RenderWindow& window;
	sf::Clock time;
	sf::CircleShape head;
	double angle;
	double angleVelocity;
	double velocity;
	std::string nickname;
	sf::Color color;
	sf::Keyboard::Key left;
	sf::Keyboard::Key right;
	sf::Vector2f position;
	sf::Vector2f oldPosition;
	bool dead;
	int &xmax;
	int &xmin;
	int &ymax;
	int& ymin;
	sf::RenderTarget& board;
	double headR;
	std::vector<sf::Vertex> trace;
	sf::VertexBuffer traceBuff;
public:
	void update();
	Player(sf::RenderWindow& win,double angle_, double R, double angvel, double vel, sf::Color col, sf::Keyboard::Key l, sf::Keyboard::Key r, int &ymax_, int & ymin_, int &xmax_, int &xmin_, sf::RenderTexture& board_);
	void setPosition(int x, int y) { position = sf::Vector2f(x, y); head.setPosition(position);	oldPosition = position; trace.push_back(sf::Vertex(sf::Vector2f(position.x - headR * sin(angle), position.y - headR * cos(angle)), color)); traceBuff.update(&trace[0], 1, 0); }
	void setNick(std::string str) { nickname = str; }
	void draw() {
		window.draw(&trace[0], trace.size(), sf::TrianglesStrip);
		/*window.draw(traceBuff);*/
		window.draw(head);
	}
	sf::Vector2f& getPos() { return position; }
	void die(bool x = true) { dead = true; }
	void checkBounds() { if (position.x < xmin || position.x > xmax || position.y > ymax || position.y < ymin) die(); }
	~Player();
};

