#include "PopAlert.h"



PopAlert::PopAlert(sf::RenderWindow & win_, std::string text_, sf::Texture & box_, sf::Texture& pres, sf::Texture& rel, sf::SoundBuffer& click_, sf::SoundBuffer& switch_, sf::Font& font_):
	window(win_),
	ok(win_, pres, rel, click_, switch_, font_)
{
	text.setFont(font_);
	text.setString(text_);
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::Black);
	drawable = false;
	box.setTexture(box_);
	box.setScale(3, 3);
	box.setPosition(win_.getSize().x / 2 - 150,  win_.getSize().y / 2 - 150);
	ok.setPosition(win_.getSize().x / 2 - 90 , win_.getSize().y / 2 + 80);
	ok.setSoundVolume(setting.SoundVolume);
	text.setPosition(win_.getSize().x / 2 - 130, win_.getSize().y / 2 - 100);
	text.setLineSpacing(1);
	ok.setTitle("ok");
}
PopAlert::~PopAlert()
{
}
