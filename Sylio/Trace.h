#pragma once
#include<vector>
#include <iostream>
#include <SFML/Graphics.hpp>
class Trace
{
private:
	std::vector<sf::Vertex> cpuMem;
	std::vector<sf::VertexBuffer> gpuMem;
	sf::Color color;
	sf::RenderWindow& window;
	int gpuTreshold;
	int begin;
	bool drawing;
public:

	Trace(sf::RenderWindow& win, sf::Color col,int aloc, int gpuT);
	~Trace();
	void update(sf::Vector2f&& left, sf::Vector2f&& right);
	inline void draw() { 
		try {//0123456789
			for (auto& x : gpuMem) 
				window.draw(x); 
			if(drawing)
				window.draw(&cpuMem[begin], cpuMem.size() - begin, sf::TrianglesStrip);
		}
		catch (...)
		{
			std::cout << "blad dostepu pamieci traceh \n";
			exit(-1);
		}
	}
	void stop();
	void start();
	bool getState() { return drawing; }
};

