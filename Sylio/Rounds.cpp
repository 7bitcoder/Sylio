#include "Rounds.h"



Rounds::Rounds(sf::RenderWindow& win, sf::Texture& box_, sf::Texture& boxOff_, sf::Texture& pointner_, sf::Texture& line_, sf::SoundBuffer& click_)
	:inputText(win, box_, boxOff_, click_),
	Slider(win, pointner_, line_, click_)
{
	min = 1;
	max = 99;
	number = 20;
	this->setString("20");
}
int Rounds::addNumber(char t)
{
	inputText::addNumber(t);
	return false;
}

int Rounds::getNumber()
{
	number = std::stoi(this->getText());
	return number;
}

bool Rounds::function()
{
	if (inputText::function(true));
	if (sliderFunction())
	{
		number = min + getValue() * (max - min);
		this->setString(std::to_string(number));
	}
	return false;
}

void Rounds::updateText()
{
	getNumber();
	std::cout << number << std::endl;
	if (number < min)
	{
		number = min;
		setString(std::to_string(number));
	}
	setSlider(double(number - min) / double(max - min));
}

Rounds::~Rounds()
{
}
