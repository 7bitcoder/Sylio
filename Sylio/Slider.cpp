#include"Music.h"
#include "Slider.h"
#include<iostream>


bool Slider::isOnPointner()
{
	//std::cout << sf::Mouse::getPosition(window).x << " " << sf::Mouse::getPosition(window).y << std::endl;
	//std::cout << button.getGlobalBounds().left << " " << button.getGlobalBounds().top << " "<< button.getGlobalBounds().height << " " << button.getGlobalBounds().width << std::endl;
	if (sf::Mouse::getPosition(window).x > pointner.getGlobalBounds().left && sf::Mouse::getPosition(window).x < (pointner.getGlobalBounds().left + pointner.getGlobalBounds().width) && sf::Mouse::getPosition(window).y > pointner.getGlobalBounds().top && sf::Mouse::getPosition(window).y < (pointner.getGlobalBounds().top + pointner.getGlobalBounds().height))
	{
		return true;
	}
	return false;
}
void Slider::checkState()
{
	if (!isOnPointner()) {

		if (state == pointnerState::isPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (!mouseAlredyPressed)
			{
				mouseAlredyPressed = true;
			}
			// left mouse button is pressed: shoot
			state = pointnerState::isPressed;
		}
		else {
			if (mouseAlredyPressed)
			{
				mouseAlredyPressed = false;
				state = pointnerState::isClickedOut;
			}
			else
				state = pointnerState::isNotPressed;
		}
	}
	else
	{

		if (!isAlredyOnButton) {
			isAlredyOut = false;
			isAlredyOnButton = true;
			state = pointnerState::apperedOn;
		}
		else {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (!mouseAlredyPressed)
				{
					mouseAlredyPressed = true;
					state = pointnerState::isClickedOn;
				}
				// left mouse button is pressed: shoot
				else
					state = pointnerState::isPressed;
			}
			else {
				if (mouseAlredyPressed)
				{
					mouseAlredyPressed = false;
					state = pointnerState::isClickedOut;
				}
				else
					state = pointnerState::isNotPressed;
			}
		}
	}
}
bool Slider::sliderFunction()//1-music/2-sound
{
	int x;
	double width;
	switch (state)
	{
	case pointnerState::isClickedOn:
		click.play();
		break;
	case pointnerState::isPressed:
		x = sf::Mouse::getPosition().x;
		if (x < line.getGlobalBounds().left)
			x = line.getGlobalBounds().left;
		if (x > line.getGlobalBounds().left + line.getGlobalBounds().width)
			x = line.getGlobalBounds().left + line.getGlobalBounds().width;
		pointner.setPosition(x, pointner.getPosition().y);
		width = pointner.getPosition().x - line.getPosition().x;
		actualval = width / line.getGlobalBounds().width;
		if (actualval != oldVal)
		{
			oldVal = actualval;
			return true;
		}
		break;
	default:
		break;
	}
	return false;
}

Slider::Slider(sf::RenderWindow& win, sf::Texture& pointner_, sf::Texture& line_, sf::SoundBuffer& click_) :pointner(pointner_), line(line_), window(win), click(click_)
{
	state = pointnerState::isNotOn;
	isAlredyOnButton = false;
	mouseAlredyPressed = false;
	isAlredyOut = false;
	actualval = oldVal = 1;

};
void Slider::setPosition(int x, int y, double scale)
{
	line.setScale(1.8, 1);
	line.setPosition(x, y);
	pointner.setOrigin(14, 0);
	pointner.setPosition(int(scale * line.getGlobalBounds().width + line.getPosition().x), line.getPosition().y);
}

void Slider::setSlider(double x)
{
	pointner.setPosition(int(x * line.getGlobalBounds().width + line.getPosition().x), line.getPosition().y);

}

Slider::~Slider()
{
}
