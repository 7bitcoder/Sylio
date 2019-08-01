#pragma once
#include<vector>
#include <iostream>
#include <SFML/Graphics.hpp>

#define NINETY_DEG 1.57079633
#define SEE_RANGE  2.26892803

class Trace
{
private:
	std::vector<sf::Vertex> cpuMem;
	std::vector<sf::VertexBuffer> gpuMem;
	sf::Color color;
	sf::RenderWindow& window;
	sf::Vector2f center;
	double R;
	double angle;
	int gpuTreshold;
	int begin;
	bool drawing;
public:

	Trace(sf::RenderWindow& win, sf::Color col, int aloc, int gpuT);
	~Trace();
	void update(sf::Vector2f& left, sf::Vector2f& right);
	inline void draw() {
		for (auto& x : gpuMem)
			window.draw(x);
		if (drawing)
			window.draw(&cpuMem[begin], cpuMem.size() - begin, sf::TrianglesStrip);
	}
	void stop(double& r, double& angle);
	void start(double& r, double& angle);
	void edge(bool beg, double& r, double& angle);
	sf::Vector2f& getLastPos() { return cpuMem.back().position; }
	sf::Vector2f& getLastLastPos() { return cpuMem[cpuMem.size() - 2].position; }
	bool getState() { return drawing; }
	int getIndex() { return cpuMem.size(); }
	int getBegin() { return begin; }
};

