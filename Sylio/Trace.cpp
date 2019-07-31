#include "Trace.h"
#include<iostream>

Trace::Trace(sf::RenderWindow& win, sf::Color col, int aloc, int gpuT)
	:window(win)
{
	gpuTreshold = gpuT;
	cpuMem.reserve(aloc);
	std::cout << cpuMem.capacity();
	begin = 0;
	color = col;
	drawing = true;
}

Trace::~Trace()
{
}

void Trace::update(sf::Vector2f& left, sf::Vector2f& right)
{
		cpuMem.push_back(sf::Vertex(left, color));
		cpuMem.push_back(sf::Vertex(right, color));
		//std::cout << cpuMem.size() << std::endl;
}

void Trace::stop(double & r, double & angle)
{
	try {
		gpuMem.push_back(sf::VertexBuffer(sf::TrianglesStrip, sf::VertexBuffer::Usage::Static));
		edge(false, r,angle);
		int diff = cpuMem.size() - begin;//0123456789
		if (!gpuMem.back().create(diff))
		{
			std::cout << "b³¹d alokacji pamieci gpu\n";
			exit(-1);
		}
		if (!gpuMem.back().update(&cpuMem[begin], diff, 0))
		{
			std::cout << "b³ad update vertexbuffer\n";
			exit(-1);
		}
	}
	catch (...)
	{
		std::cout << "blad push back gpu\n";
		exit(-1);
	}
	begin = cpuMem.size();
	drawing = false;
}

void Trace::start(double & r, double & angle)
{
	edge(true, r, angle);
	drawing = true;
}
void Trace::edge(bool beg, double & R, double & angle)
{
	sf::Vector2f& right = cpuMem.back().position;
	sf::Vector2f& left = cpuMem[cpuMem.size() - 2].position;
	sf::Vector2f cent((right.x + left.x) / 2, (right.y + left.y) / 2);
	double ang = NINETY_DEG / 5;
	if (beg)
	{
		for (int i = 0; i < 5; i++)
		{
			sf::Vector2f point(R * sin(angle + 2.0 * NINETY_DEG - i * ang) + cent.x, R * cos(angle + 2 * NINETY_DEG - i * ang) + cent.y);
			cpuMem.push_back(sf::Vertex(point, color));
			point.x = R * sin(angle + 2 * NINETY_DEG + i * ang) + cent.x;
			point.y = R * cos(angle + 2 * NINETY_DEG + i * ang) + cent.y;
			cpuMem.push_back(sf::Vertex(point, color));
		}
	}
	else
	{
		for (int i = 1; i < 6; i++)
		{
			sf::Vector2f point(R * sin(angle + NINETY_DEG - i * ang) + cent.x, R * cos(angle + NINETY_DEG - i * ang) + cent.y);
			cpuMem.push_back(sf::Vertex(point, color));
			point.x = R * sin(angle - NINETY_DEG + i * ang) + cent.x;
			point.y = R * cos(angle - NINETY_DEG + i * ang) + cent.y;
			cpuMem.push_back(sf::Vertex(point, color));
		}
	}
}