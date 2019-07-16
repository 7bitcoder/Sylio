#include "PopAlert.h"



PopAlert::PopAlert(sf::RenderWindow & win_, std::string text_, sf::Texture & box_, sf::Texture& pres, sf::Texture& rel,sf::Texture& off, sf::SoundBuffer& click_, sf::SoundBuffer& switch_, sf::Font& font_):
	window(win_),
	ok(win_, pres, rel, off, click_, switch_, font_)
{
	text.setFont(font_);
	text.setString(text_);
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::Black);
	drawable = false;
	box.setTexture(box_);
	box.setPosition(win_.getSize().x / 2 - 200,  win_.getSize().y / 2 - 70);
	ok.setPosition(box.getPosition().x + 110, box.getPosition().y + 135);
	ok.setSoundVolume(setting.SoundVolume);
	text.setPosition(box.getPosition().x + 20, box.getPosition().y + 20);
	text.setLineSpacing(1);
	ok.setTitle("ok");
}
PopAlert::~PopAlert()
{
}
