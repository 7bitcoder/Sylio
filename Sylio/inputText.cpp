#include "inputText.h"


bool inputText::focused = false;
inputText::inputText(sf::RenderWindow& win, sf::Texture& box_, sf::SoundBuffer& click_) : window(win), box(box_),  click(click_)
{
	buttonSt = buttonState::isNotPressed;
	positionSt = positionState::isNotOn;
	lastButtonSt = buttonSt;
	lastPositionSt = positionSt;
	clicked = false;
	activated = false;
}
bool inputText::function()
{
	if (positionSt == positionState::isNotOn && lastPositionSt == positionState::isNotOn && clicked == false)
		return false;
	else if (clicked == false && positionSt == positionState::isOn && buttonSt == buttonState::isPressed && lastButtonSt == buttonState::isNotPressed)
	{
		click.play();
		clicked = true;
	}
	else if (clicked == true && positionSt == positionState::isOn && buttonSt == buttonState::isNotPressed && lastButtonSt == buttonState::isPressed)
	{
		focused = true;
		clicked = false;
		if (!activated)
		{
			activated = true;
			text.clear();
			textOutput.setString("");
		}
		return true;
	}
	return false;
}
bool inputText::setChar(char t)//event.text.unicode)
{
	if (t == 8)
	{
		if (text.empty())
			return false;
		text.pop_back();
		textOutput.setString(text);
		return false;
	}
	if (t == 13)
	{
		focused = false;
		return true;
	}
	if (t < 20 || t >126)
		return false;
	text += t;
	textOutput.setString(text);
	if (textOutput.getGlobalBounds().width > box.getGlobalBounds().width)
	{
		text.pop_back();
		textOutput.setString(text);
		return false;
	}
	return false;
}

void inputText::checkState()
{
	lastButtonSt = buttonSt;
	lastPositionSt = positionSt;
	if (isOnButton())
		positionSt = positionState::isOn;
	else
		positionSt = positionState::isNotOn;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		buttonSt = buttonState::isPressed;
	else
		buttonSt = buttonState::isNotPressed;
}
bool inputText::isOnButton()
{
	//std::cout << sf::Mouse::getPosition(window).x << " " << sf::Mouse::getPosition(window).y << std::endl;
	//std::cout << button.getGlobalBounds().left << " " << button.getGlobalBounds().top << " "<< button.getGlobalBounds().height << " " << button.getGlobalBounds().width << std::endl;
	if (sf::Mouse::getPosition(window).x > box.getGlobalBounds().left && sf::Mouse::getPosition(window).x < (box.getGlobalBounds().left + box.getGlobalBounds().width) && sf::Mouse::getPosition(window).y > box.getGlobalBounds().top && sf::Mouse::getPosition(window).y < (box.getGlobalBounds().top + box.getGlobalBounds().height))
	{
		return true;
	}
	return false;
}
void inputText::defaultString(std::string x)
{
	text = x;
	textOutput.setString(x);
}
void inputText::setPosition(int x, int y)
{
	box.setPosition(x, y);
	box.setScale(1.8, 1);
	textOutput.setPosition(x + 5, y + 10);
}
inputText::~inputText()
{
}
