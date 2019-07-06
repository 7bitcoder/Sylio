#include "menu.h"
#include<SFML/Graphics.hpp>
#include<iostream>
#include<filesystem>
#include<SFML/Audio.hpp>

bool Menu::isOnButton(sf::Sprite & sprite)
{
	//std::cout << sf::Mouse::getPosition(window).x << " " << sf::Mouse::getPosition(window).y << std::endl;
	//std::cout << sprite.getGlobalBounds().left << " " << sprite.getGlobalBounds().top << " "<< sprite.getGlobalBounds().height << " " << sprite.getGlobalBounds().width << std::endl;

	if (sf::Mouse::getPosition(window).x > sprite.getGlobalBounds().left && sf::Mouse::getPosition(window).x < (sprite.getGlobalBounds().left + sprite.getGlobalBounds().width) && sf::Mouse::getPosition(window).y > sprite.getGlobalBounds().top && sf::Mouse::getPosition(window).y < (sprite.getGlobalBounds().top + sprite.getGlobalBounds().height))
		return true;
	return false;
}

bool Menu::isAlredyOnButton(sf::Sprite& sprite)
{
	return false;
}

int Menu::update()
{
	sf::Font font;
	if (!font.loadFromFile("../Font/kenvector_future.ttf"))
		return -1;

	sf::Text title;
	title.setFont(font);
	title.setCharacterSize(140);
	title.setString("Sylio");
	title.setPosition(window.getSize().x/2 - 250, window.getSize().y/2 - 300);
	title.setFillColor(sf::Color::Black);

	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("../Bonus/switch3.ogg"))
		return -1;
	sf::Sound switch1;
	switch1.setBuffer(buffer);
	switch1.setVolume(30);

	sf::SoundBuffer buffer2;
	if (!buffer2.loadFromFile("../Bonus/click1.ogg"))
		return -1;
	sf::Sound click;
	click.setBuffer(buffer2);

	sf::Texture back;
	if (!back.loadFromFile("../background.jpg"))
		return -1;
	sf::Sprite background;
	background.setTexture(back);

	sf::Text ver;
	ver.setFont(font);
	ver.setCharacterSize(15);
	ver.setString(version);
	ver.setPosition(window.getSize().x - 100,window.getSize().y - 15);

	sf::Texture ex;
	if (!ex.loadFromFile("../PNG/red_boxCross.png"))
		return -1;
	sf::Sprite exit(ex);
	exit.setPosition(window.getSize().x - 40, 0);

	sf::Texture mar;
	if (!mar.loadFromFile("../PNG/green_sliderRight.png"))
		return -1;
	sf::Sprite mark(mar);
	mark.setPosition(-200, -200);

	sf::Texture block;
	if (!block.loadFromFile("../PNG/green_button00.png"))
		std::cout << "block load error";

	sf::Texture blockPressed;
	if (!blockPressed.loadFromFile("../PNG/green_button05.png"))
		return -1;

	sf::Sprite blockNormalGame(block);
	sf::Sprite blockSettings(block);
	sf::Sprite blockQuit(block);
	sf::Sprite blockMultiplayerGame(block);
	blockNormalGame.setScale(1.8, 1);
	blockNormalGame.setPosition(window.getSize().x / 2 - 190*1.8/2, window.getSize().y / 2 - 50);
	
	sf::Text NormalGame;
	NormalGame.setFont(font);
	NormalGame.setCharacterSize(25);
	NormalGame.setString("Normal Game");
	NormalGame.setPosition(blockNormalGame.getPosition().x + 20, blockNormalGame.getPosition().y + 8);

	blockMultiplayerGame.setScale(1.8, 1);
	blockMultiplayerGame.setPosition(window.getSize().x / 2 - 190 * 1.8 / 2, window.getSize().y / 2 - 50 + 100);

	sf::Text MultiplayerGame;
	MultiplayerGame.setFont(font);
	MultiplayerGame.setCharacterSize(25);
	MultiplayerGame.setString("Multiplayer Game");
	MultiplayerGame.setPosition(blockMultiplayerGame.getPosition().x + 20, blockMultiplayerGame.getPosition().y + 8 );

	blockSettings.setScale(1.8, 1);
	blockSettings.setPosition(window.getSize().x / 2 - 190 * 1.8 / 2, window.getSize().y / 2 - 50 + 200);

	sf::Text Settings;
	Settings.setFont(font);
	Settings.setCharacterSize(25);
	Settings.setString("Settings");
	Settings.setPosition(blockSettings.getPosition().x + 20, blockSettings.getPosition().y + 8);

	blockQuit.setScale(1.8, 1);
	blockQuit.setPosition(window.getSize().x / 2 - 190 * 1.8 / 2, window.getSize().y / 2 - 50 + 300);

	sf::Text Quit;
	Quit.setFont(font);
	Quit.setCharacterSize(25);
	Quit.setString("Quit");
	Quit.setPosition(blockQuit.getPosition().x + 20, blockQuit.getPosition().y + 8);

	bool isAlredyOnN = false;
	bool mouseAlredyPressed = false;
	bool isAlredyOnD = false;
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (isOnButton(blockNormalGame)) {
				if (!isAlredyOnN) {
					mark.setPosition(blockNormalGame.getPosition().x - 50, blockNormalGame.getPosition().y + 10);
					switch1.play();
					isAlredyOnN = true;
					isAlredyOnD = false;
				}
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					if (!mouseAlredyPressed)
					{
						blockNormalGame.setTexture(blockPressed);
						mouseAlredyPressed = true;
						click.play();
					}
					// left mouse button is pressed: shoot
				}
				else
					if (mouseAlredyPressed)
					{
						blockNormalGame.setTexture(block);
						mouseAlredyPressed = false;
					}
			}
			else if (isOnButton(blockMultiplayerGame)) {
					if (!isAlredyOnN) {
						mark.setPosition(blockMultiplayerGame.getPosition().x - 50, blockMultiplayerGame.getPosition().y + 10);
						switch1.play();
						isAlredyOnN = true;
						isAlredyOnD = false;
					}
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						if (!mouseAlredyPressed)
						{
							blockMultiplayerGame.setTexture(blockPressed);
							mouseAlredyPressed = true;
							click.play();
						}
						// left mouse button is pressed: shoot
					}
					else
						if (mouseAlredyPressed)
						{
							blockMultiplayerGame.setTexture(block);
							mouseAlredyPressed = false;
						}
			}
			else if (isOnButton(blockSettings)) {
				if (!isAlredyOnN) {
					mark.setPosition(blockSettings.getPosition().x - 50, blockSettings.getPosition().y + 10);
					switch1.play();
					isAlredyOnN = true;
					isAlredyOnD = false;
				}
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					if (!mouseAlredyPressed)
					{
						blockSettings.setTexture(blockPressed);
						mouseAlredyPressed = true;
						click.play();
					}
					// left mouse button is pressed: shoot
				}
				else
					if (mouseAlredyPressed)
					{
						blockSettings.setTexture(block);
						mouseAlredyPressed = false;
					}
			}
		    else if (isOnButton(blockQuit)) {
					if (!isAlredyOnN) {
						mark.setPosition(blockQuit.getPosition().x - 50, blockQuit.getPosition().y + 10);
						switch1.play();
						isAlredyOnN = true;
						isAlredyOnD = false;
					}
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						if (!mouseAlredyPressed)
						{
							blockQuit.setTexture(blockPressed);
							mouseAlredyPressed = true;
							click.play();
						}
						// left mouse button is pressed: shoot
					}
					else
						if (mouseAlredyPressed)
						{
							blockQuit.setTexture(block);
							mouseAlredyPressed = false;
							return 5;
						}
				}
				//std::cout << "dd\n";
			else {
				mouseAlredyPressed = false;
				if (isAlredyOnD == false) {
					mark.setPosition(-200, -200);
					isAlredyOnN = false;
					isAlredyOnD = true;
				}
			}
		}

		// clear the window with black color
		window.clear(sf::Color::Black);

		// draw everything here...
		// window.draw(...);
		window.draw(background);
		window.draw(ver);
		window.draw(title);

		window.draw(blockNormalGame);
		window.draw(NormalGame);

		window.draw(blockMultiplayerGame);
		window.draw(MultiplayerGame);

		window.draw(blockSettings);
		window.draw(Settings);

		window.draw(blockQuit);
		window.draw(Quit);

		window.draw(mark);
		// end the current frame
		window.display();
	}
}
Menu::~Menu()
{
}
