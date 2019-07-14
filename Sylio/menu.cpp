#include "menu.h"

Menu::Menu(sf::RenderWindow& win, std::string& ver_): window(win), version(ver_), background(win)
{
	if (!clickBuff.loadFromFile("../Sounds/click1.ogg"))
		exit(-1);

	if (!switchBuff.loadFromFile("../Sounds/switch2.ogg"))
		exit(-1);

	if (!font.loadFromFile("../Font/kenvector_future.ttf"))
		exit(-1);
	
	if (!font.loadFromFile("../Font/kenvector_future.ttf"))
		exit(-1);

	if (!block.loadFromFile("../PNG/grey_button15.png"))
		exit(-1);

	if (!blockPressed.loadFromFile("../PNG/grey_button00.png"))
		exit(-1);

	if (!back.loadFromFile("../stars_space_sky_glitter_116409_1920x108022.jpg"))
		exit(-1);

	if (!base.loadFromFile("../base3.png"))
		exit(-1);
	//background.setTexture(back);
	background.set(back,base, 0 , 0.0015);

	if (!mar.loadFromFile("../PNG/grey_sliderRight.png"))
		exit(-1);

	if (!VolumeSliderLine.loadFromFile("../PNG/grey_sliderHorizontal.png"))
		exit(-1);

	if (!VolumePointner.loadFromFile("../PNG/grey_sliderUp.png"))
		exit(-1);

	if (!listBlock.loadFromFile("../PNG/grey_button06.png"))
		exit(-1);

	mark.setTexture(mar);
	mark.setPosition(-200, -200);



}

st Menu::mainMenuUpdate()
{
	sf::Text title;
	title.setFont(font);
	title.setCharacterSize(140);
	title.setString("Sylio");
	title.setPosition(window.getSize().x / 2 - 250, window.getSize().y / 2 - 300);
	title.setFillColor(sf::Color::Black);

	sf::Text ver;
	ver.setFont(font);
	ver.setCharacterSize(15);
	ver.setString(version);
	ver.setPosition(window.getSize().x - 100, window.getSize().y - 15);

	mark.setPosition(-200, -200);

	Button normalGame(window, blockPressed, block, mark, clickBuff, switchBuff, font);
	normalGame.setPosition(window.getSize().x / 2 - 190 * 1.8 / 2, window.getSize().y / 2 - 100);
	normalGame.setTitle("normal game");
	normalGame.setSoundVolume(setting.SoundVolume);

	Button multiplayerGame(window, blockPressed, block, mark, clickBuff, switchBuff, font);
	multiplayerGame.setPosition(window.getSize().x / 2 - 190 * 1.8 / 2, window.getSize().y / 2);
	multiplayerGame.setTitle("multipleyer game");
	multiplayerGame.setSoundVolume(setting.SoundVolume);

	Button settings(window, blockPressed, block, mark, clickBuff, switchBuff, font);
	settings.setPosition(window.getSize().x / 2 - 190 * 1.8 / 2, window.getSize().y / 2 + 100);
	settings.setTitle("settings");
	settings.setSoundVolume(setting.SoundVolume);
	
	Button quit(window, blockPressed, block, mark, clickBuff, switchBuff, font);
	quit.setPosition(window.getSize().x / 2 - 190 * 1.8 / 2, window.getSize().y / 2 + 200);
	quit.setTitle("quit");
	quit.setSoundVolume(setting.SoundVolume);

	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			normalGame.checkState();
			multiplayerGame.checkState();
			settings.checkState();
			quit.checkState();
			if (normalGame.buttonFunction());
			else if (multiplayerGame.buttonFunction());
			else if (settings.buttonFunction())
				return st::settings;
			else if (quit.buttonFunction())
				return st::quit;
			else ;
		}

		window.clear(sf::Color::Black);

		background.draw();
		window.draw(ver);
		window.draw(title);

		normalGame.draw();
		multiplayerGame.draw();
		settings.draw();
		quit.draw();
		window.draw(mark);
		window.display();
	}
}
st Menu::settingsUupdate()
{
	int linex = window.getSize().x / 2 - 190 * 1.8 / 2;
	int liney = window.getSize().y / 2 - 50;

	mark.setPosition(-200, -200);
	sf::Event event;


	sf::Text VolMusicText;
	VolMusicText.setString("Music Volume");
	VolMusicText.setFont(font);
	VolMusicText.setCharacterSize(25);
	VolMusicText.setPosition(linex + 20, liney - 400 + 8);// .getPosition().x + 20, VolumeMusic.getPosition().y + 8);


	sf::Text VolSounndEffectsTest;
	VolSounndEffectsTest.setString("Sound Effects Volume");
	VolSounndEffectsTest.setFont(font);
	VolSounndEffectsTest.setCharacterSize(25);
	VolSounndEffectsTest.setPosition(linex + 20, liney- 200 + 8); //(VolumeSoundEffects.getPosition().x + 20, VolumeSoundEffects.getPosition().y + 8);


	sf::Text ChoseMusicText;
	ChoseMusicText.setString("Chose music file");
	ChoseMusicText.setFont(font);
	ChoseMusicText.setCharacterSize(25);
	ChoseMusicText.setPosition(linex + 20, liney - 50 + 8); //(ChoseMusic.getPosition().x + 20, ChoseMusic.getPosition().y + 8);


	sf::Text fileError;
	fileError.setString("could not open file");
	fileError.setFont(font);
	fileError.setCharacterSize(15);
	fileError.setPosition(-200, -200); //(ChoseMusic.getPosition().x + 20, ChoseMusic.getPosition().y + 8);
	fileError.setFillColor(sf::Color::Red);
	
	Slider musicSlider(window, VolumePointner, VolumeSliderLine, clickBuff);
	musicSlider.setPosition(linex, liney - 300, 1);//1- music /2 -sound
	musicSlider.setSoundVolume(setting.SoundVolume);

	Slider soundSlider(window, VolumePointner, VolumeSliderLine, clickBuff);
	soundSlider.setPosition(linex, liney - 100, 2);
	soundSlider.setSoundVolume(setting.SoundVolume);

	List list;
	std::filesystem::path directory = "../Music";

	int i = 0;
	for (const auto& entry : std::filesystem::directory_iterator(directory))
	{
		//std::cout << entry.path().generic_string() << " to tutaj"<< std::endl;
		list.pushBack(window, blockPressed, listBlock, mark, clickBuff, switchBuff, font);
		list.setPosition(linex, liney + 50 + i * 50);
		list.setText(entry.path().filename().generic_string());
		i++;
		if (i == 5)
			break;
	}
	list.setSoundVolume(setting.SoundVolume);

	Button goBack(window, blockPressed, block, mark, clickBuff, switchBuff, font);
	goBack.setPosition(linex, liney + 200 + 4 * 58);
	goBack.setTitle("Back");
	goBack.setSoundVolume(setting.SoundVolume);

	Button musicApply(window, blockPressed, block, mark, clickBuff, switchBuff, font);
	musicApply.setPosition(linex, liney + 100 + 4 * 58);
	musicApply.setTitle("apply");
	musicApply.setSoundVolume(setting.SoundVolume);

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{

			goBack.checkState();
			musicApply.checkState();
			musicSlider.checkState();
			soundSlider.checkState();
			list.checkState();
			if (goBack.buttonFunction())
				return st::mainMenu;
			else if (musicApply.buttonFunction())
			{
				bool try_ = music.setGameMusic(list.getFileDirect());
				if (try_)
					fileError.setPosition(-200, -200);
				else
					fileError.setPosition(linex + 20, liney + 8);
			}
			else if (musicSlider.sliderFunction());
			else if (soundSlider.sliderFunction())
			{
				musicSlider.setSoundVolume(setting.SoundVolume);
				soundSlider.setSoundVolume(setting.SoundVolume);
				goBack.setSoundVolume(setting.SoundVolume);
				list.setSoundVolume(setting.SoundVolume);
				musicApply.setSoundVolume(setting.SoundVolume);
			}
			else;
		}
		window.clear(sf::Color::Black);

		background.draw();
		goBack.draw();
		musicSlider.draw();
		soundSlider.draw();
		list.draw();
		musicApply.draw();

		window.draw(fileError);
		window.draw(ChoseMusicText);
		window.draw(VolMusicText);
		window.draw(VolSounndEffectsTest);
		window.draw(mark);
		window.display();
	}
	return st::mainMenu;
}
Menu::~Menu()
{
}
