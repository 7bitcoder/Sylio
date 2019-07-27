#include "Trace.h"
#include<iostream>

Trace::Trace(sf::RenderWindow& win, sf::Color col, int aloc, int gpuT)
	:window(win)
{
	gpuTreshold = gpuT;
	cpuMem.reserve(aloc);
	begin = 0;
	color = col;
	drawing = true;
}

Trace::~Trace()
{
}

void Trace::update(sf::Vector2f&& left, sf::Vector2f&& right)
{
		cpuMem.push_back(sf::Vertex(left, color));
		cpuMem.push_back(sf::Vertex(right, color));
		//std::cout << cpuMem.size() << std::endl;
	/*if (!(cpuMem.size() % gpuTreshold))
	{
		gpuMem.push_back(sf::VertexBuffer(sf::TrianglesStrip, sf::VertexBuffer::Usage::Static));
		gpuMem.back().create(gpuTreshold);
		gpuMem.back().update(&cpuMem[start], gpuTreshold, 0);
		start += gpuTreshold;
	}*/
}

void Trace::stop()
{
	try {
		gpuMem.push_back(sf::VertexBuffer(sf::TrianglesStrip, sf::VertexBuffer::Usage::Static));
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

void Trace::start()
{
	drawing = true;
}
