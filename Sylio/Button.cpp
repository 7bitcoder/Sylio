#include "Button.h"



void Button::showMark()
{
	Mark.setPosition(button.getPosition().x - 50, button.getPosition().y + 10);
}

void Button::hideMark()
{
	Mark.setPosition(-200,-200);
}

void Button::clickSound()
{
	click.play();
}

void Button::switchSound()
{
	switchS.play();
}

bool Button::buttonFunction()
{
	//std::cout << state;
	if (positionSt == positionState::isNotOn && lastPositionSt == positionState::isNotOn && clicked == false)
		return false;
	else if (positionSt == positionState::isOn && lastPositionSt == positionState::isNotOn)
	{
		switchS.play();
		showMark();
	}
	else if (clicked == false && positionSt == positionState::isOn && buttonSt == buttonState::isPressed && lastButtonSt == buttonState::isNotPressed)
	{	
		click.play();
		button.move(0, 4);
		title.move(0, 4);
		button.setTexture(pressed, true);
		clicked = true;
	}
	else if (clicked == true && positionSt == positionState::isOn && buttonSt == buttonState::isNotPressed && lastButtonSt == buttonState::isPressed )
	{
		button.move(0, -4);
		title.move(0, -4);
		button.setTexture(released, true);
		clicked = false;
		return true;
	}
	else if (clicked == true && positionSt == positionState::isNotOn && lastPositionSt == positionState::isOn)
	{
		button.move(0, -4);
		title.move(0, -4);
		button.setTexture(released, true);
		clicked = false;
		hideMark();
	}
	else if (positionSt == positionState::isNotOn && lastPositionSt == positionState::isOn)
	{
		hideMark();
	}
	return false;
}
bool Button::settingsListFunction()
{
	if (positionSt == positionState::isNotOn && lastPositionSt == positionState::isNotOn && clicked == false)
		return false;
	else if (positionSt == positionState::isOn && lastPositionSt == positionState::isNotOn)
	{
		switchS.play();
	}
	else if (clicked == false && positionSt == positionState::isOn && buttonSt == buttonState::isPressed && lastButtonSt == buttonState::isNotPressed)
	{
		click.play();
		clicked = true;
	}
	else if (clicked == true && positionSt == positionState::isOn && buttonSt == buttonState::isNotPressed && lastButtonSt == buttonState::isPressed)
	{
		return true;
	}
	return false;
}
void Button::setTitle(std::string title_)
{
	text = title_;
	title.setFont(font);
	title.setCharacterSize(25);
	title.setFillColor(sf::Color::Black);
	title.setString(title_);
	if (title.getGlobalBounds().width > button.getGlobalBounds().width)
	{
		while (title.getGlobalBounds().width > button.getGlobalBounds().width)
		{
			title_.pop_back();
			title.setString(title_);
		}
		title_.pop_back();
		title_.pop_back();
		title_.pop_back();
		title_ += "...";
		title.setString(title_);
	}
	title.setPosition(button.getPosition().x + 20, button.getPosition().y + 8);
}
void Button::setPosition(int posx, int posy)
{
	button.setPosition(posx, posy);
}
Button::Button(sf::RenderWindow & win, sf::Texture& pres, sf::Texture& rel, sf::Sprite& mark_, sf::SoundBuffer &click_, sf::SoundBuffer &switch_,sf::Font &font_): 
	font(font_),
	Mark(mark_), 
	switchS(switch_),
	click(click_) ,
	window(win), 
	pressed(pres), 
	released(rel)
{
	switchS.setVolume(30);
	button.setScale(1.8, 1);
	button.setTexture(rel);
	buttonSt = buttonState::isNotPressed;
	positionSt = positionState::isNotOn;
	lastButtonSt = buttonSt;
	lastPositionSt = positionSt;
	clicked = false;
}

void Button::checkState()
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
bool Button::isOnButton()
{
	//std::cout << sf::Mouse::getPosition(window).x << " " << sf::Mouse::getPosition(window).y << std::endl;
	//std::cout << button.getGlobalBounds().left << " " << button.getGlobalBounds().top << " "<< button.getGlobalBounds().height << " " << button.getGlobalBounds().width << std::endl;
	if (sf::Mouse::getPosition(window).x > button.getGlobalBounds().left && sf::Mouse::getPosition(window).x < (button.getGlobalBounds().left + button.getGlobalBounds().width) && sf::Mouse::getPosition(window).y > button.getGlobalBounds().top && sf::Mouse::getPosition(window).y < (button.getGlobalBounds().top + button.getGlobalBounds().height))
	{	
		return true;
	}
	return false;
}

Button::~Button()
{
}
