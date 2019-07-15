#include "Button.h"



void Button::showMark()
{
	Mark.setPosition(this->getPosition().x - 50, this->getPosition().y + 10);
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
		this->move(0, 4);
		title.move(0, 4);
		this->setTexture(pressed, true);
		clicked = true;
	}
	else if (clicked == true && positionSt == positionState::isOn && buttonSt == buttonState::isNotPressed && lastButtonSt == buttonState::isPressed )
	{
		this->move(0, -4);
		title.move(0, -4);
		this->setTexture(released, true);
		clicked = false;
		return true;
	}
	else if (clicked == true && positionSt == positionState::isNotOn && lastPositionSt == positionState::isOn)
	{
		this->move(0, -4);
		title.move(0, -4);
		this->setTexture(released, true);
		clicked = false;
		hideMark();
	}
	else if (positionSt == positionState::isNotOn && lastPositionSt == positionState::isOn)
	{
		hideMark();
	}
	return false;
}
bool Button::normalButtonFunction()
{
	//std::cout << state;
	if (positionSt == positionState::isNotOn && lastPositionSt == positionState::isNotOn && clicked == false)
		return false;
	else if (positionSt == positionState::isOn && lastPositionSt == positionState::isNotOn)
	{
		switchS.play();
	}
	else if (clicked == false && positionSt == positionState::isOn && buttonSt == buttonState::isPressed && lastButtonSt == buttonState::isNotPressed)
	{
		click.play();
		this->move(0, 4);
		title.move(0, 4);
		this->setTexture(pressed, true);
		clicked = true;
	}
	else if (clicked == true && positionSt == positionState::isOn && buttonSt == buttonState::isNotPressed && lastButtonSt == buttonState::isPressed)
	{
		this->move(0, -4);
		title.move(0, -4);
		this->setTexture(released, true);
		clicked = false;
		return true;
	}
	else if (clicked == true && positionSt == positionState::isNotOn && lastPositionSt == positionState::isOn)
	{
		this->move(0, -4);
		title.move(0, -4);
		this->setTexture(released, true);
		clicked = false;
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
	if (title.getGlobalBounds().width > this->getGlobalBounds().width)
	{
		while (title.getGlobalBounds().width > this->getGlobalBounds().width)
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
	title.setPosition(this->getPosition().x + 20, this->getPosition().y + 8);
}
Button::Button(sf::RenderWindow & win, sf::Texture& pres, sf::Texture& rel, sf::Texture& mark_, sf::SoundBuffer &click_, sf::SoundBuffer &switch_,sf::Font &font_): 
	font(font_),
	switchS(switch_),
	click(click_) ,
	window(win), 
	pressed(pres), 
	released(rel)
{
	Mark.setTexture(mark_);
	switchS.setVolume(30);
	this->setTexture(rel);
	buttonSt = buttonState::isNotPressed;
	positionSt = positionState::isNotOn;
	lastButtonSt = buttonSt;
	lastPositionSt = positionSt;
	clicked = false;
	hideMark();
}
Button::Button(sf::RenderWindow& win, sf::Texture& pres, sf::Texture& rel, sf::SoundBuffer& click_, sf::SoundBuffer& switch_, sf::Font& font_) :
	font(font_),
	switchS(switch_),
	click(click_),
	Mark(),
	window(win),
	pressed(pres),
	released(rel)
{
	switchS.setVolume(30);
	this->setTexture(rel);
	buttonSt = buttonState::isNotPressed;
	positionSt = positionState::isNotOn;
	lastButtonSt = buttonSt;
	lastPositionSt = positionSt;
	clicked = false;
	hideMark();
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
	if (sf::Mouse::getPosition(window).x > this->getGlobalBounds().left && sf::Mouse::getPosition(window).x < (this->getGlobalBounds().left + this->getGlobalBounds().width) && sf::Mouse::getPosition(window).y > this->getGlobalBounds().top && sf::Mouse::getPosition(window).y < (this->getGlobalBounds().top + this->getGlobalBounds().height))
	{	
		return true;
	}
	return false;
}

Button::~Button()
{
}
