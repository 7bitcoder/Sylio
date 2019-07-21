#include "menu.h"

Menu::Menu(sf::RenderWindow& win, std::string& ver_): window(win), version(ver_), background(win)
{

	if (!clickBuff.loadFromFile("../Sounds/click1.ogg"))
		exit(-1);

	if (!switchBuff.loadFromFile("../Sounds/switch2.ogg"))
		exit(-1);

	if (!font.loadFromFile("../Font/kenvector_future.ttf"))
		exit(-1);

	if (!checkOff.loadFromFile("../PNG/grey_box.png"))
		exit(-1);

	
	if (!checkOnBlue.loadFromFile("../PNG/blue_boxCheckmark.png"))
		exit(-1);
	
	if (!controlOnBlue.loadFromFile("../PNG/blue_button06.png"))
		exit(-1);

	if (!controlOffBlue.loadFromFile("../PNG/blue_button11.png"))
		exit(-1);

	if (!nickNameOnBlue.loadFromFile("../PNG/blue_button13.png"))
		exit(-1);

	if (!nickNameOffBlue.loadFromFile("../PNG/blue_button04.png"))
		exit(-1);

	
	if (!checkOnGreen.loadFromFile("../PNG/green_boxCheckmark.png"))
		exit(-1);

	if (!controlOnGreen.loadFromFile("../PNG/green_button06.png"))
		exit(-1);

	if (!controlOffGreen.loadFromFile("../PNG/green_button11.png"))
		exit(-1);

	if (!nickNameOnGreen.loadFromFile("../PNG/green_button13.png"))
		exit(-1);

	if (!nickNameOffGreen.loadFromFile("../PNG/green_button04.png"))
		exit(-1);

	
	if (!checkOnYellow.loadFromFile("../PNG/yellow_boxCheckmark.png"))
		exit(-1);

	if (!controlOnYellow.loadFromFile("../PNG/yellow_button06.png"))
		exit(-1);

	if (!controlOffYellow.loadFromFile("../PNG/yellow_button11.png"))
		exit(-1);

	if (!nickNameOnYellow.loadFromFile("../PNG/yellow_button13.png"))
		exit(-1);

	if (!nickNameOffYellow.loadFromFile("../PNG/yellow_button04.png"))
		exit(-1);


	if (!checkOnRed.loadFromFile("../PNG/red_boxCheckmark.png"))
		exit(-1);

	if (!controlOnRed.loadFromFile("../PNG/red_button03.png"))
		exit(-1);

	if (!controlOffRed.loadFromFile("../PNG/red_button08.png"))
		exit(-1);

	if (!nickNameOnRed.loadFromFile("../PNG/red_button10.png"))
		exit(-1);

	if (!nickNameOffRed.loadFromFile("../PNG/red_button01.png"))
		exit(-1);



	if (!block.loadFromFile("../PNG/grey_button15.png"))
		exit(-1);

	if (!blockPressed.loadFromFile("../PNG/grey_button00.png"))
		exit(-1);

	if (!offButton.loadFromFile("../PNG/grey_button03.png"))
		exit(-1);

	if (!back.loadFromFile("../stars_space_sky_glitter_116409_1920x108022.jpg"))
		exit(-1);

	if (!whiteBox.loadFromFile("../PNG/grey_panel.png"))
		exit(-1);

	if (!base.loadFromFile("../base3.png"))
		exit(-1);
	//background.setTexture(back);
	background.set(back,base, 0 , 0.002);

	if (!mar.loadFromFile("../PNG/grey_sliderRight.png"))
		exit(-1);

	if (!VolumeSliderLine.loadFromFile("../PNG/grey_sliderHorizontal.png"))
		exit(-1);

	if (!VolumePointner.loadFromFile("../PNG/grey_sliderUp.png"))
		exit(-1);

	if (!listBlock.loadFromFile("../PNG/grey_button06.png"))
		exit(-1);

}

st Menu::mainMenuUpdate()
{
	sf::Text title;
	title.setFont(font);
	title.setCharacterSize(140);
	title.setString("Sylio");
	title.setPosition(window.getSize().x / 2 - 250, window.getSize().y / 2 - 300);
	title.setFillColor(sf::Color::White);

	sf::Text ver;
	ver.setFont(font);
	ver.setCharacterSize(15);
	ver.setString(version);
	ver.setPosition(window.getSize().x - 100, window.getSize().y - 15);

	Button normalGame(window, blockPressed, block, offButton, clickBuff, switchBuff, font);
	normalGame.setPosition(window.getSize().x / 2 - 190 * 1.8 / 2, window.getSize().y / 2 - 100);
	normalGame.setScale(1.8, 1);
	normalGame.setTitle("normal game");
	normalGame.setSoundVolume(setting.SoundVolume);


	Button multiplayerGame(window, blockPressed, block, offButton, clickBuff, switchBuff, font);
	multiplayerGame.setPosition(window.getSize().x / 2 - 190 * 1.8 / 2, window.getSize().y / 2);
	multiplayerGame.setScale(1.8, 1);
	multiplayerGame.setTitle("multipleyer game");
	multiplayerGame.setSoundVolume(setting.SoundVolume);


	Button settings(window, blockPressed, block, offButton, clickBuff, switchBuff, font);
	settings.setPosition(window.getSize().x / 2 - 190 * 1.8 / 2, window.getSize().y / 2 + 100);
	settings.setScale(1.8, 1);
	settings.setTitle("settings");
	settings.setSoundVolume(setting.SoundVolume);

	
	Button quit(window, blockPressed, block, offButton, clickBuff, switchBuff, font);
	quit.setPosition(window.getSize().x / 2 - 190 * 1.8 / 2, window.getSize().y / 2 + 200);
	quit.setScale(1.8, 1);
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
			if (normalGame.buttonFunction())
				return st::normalGame;
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
		window.display();
	}
}
st Menu::settingsUupdate()
{
	PopAlert alert(window, "asdasd", whiteBox, blockPressed, block, offButton, clickBuff, switchBuff, font);

	int linex = window.getSize().x / 2 - 190 * 1.8 / 2;
	int liney = window.getSize().y / 2 - 50;

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
	musicSlider.setPosition(linex, liney - 300, (music.getVolume() / 30));//1- music /2 -sound
	musicSlider.setSoundVolume(setting.MusicVolume);

	Slider soundSlider(window, VolumePointner, VolumeSliderLine, clickBuff);
	soundSlider.setPosition(linex, liney - 100, setting.SoundVolume);
	soundSlider.setSoundVolume(setting.SoundVolume);

	List list;
	std::filesystem::path directory = "../Music";

	int i = 0;
	for (const auto& entry : std::filesystem::directory_iterator(directory))
	{
		//std::cout << entry.path().generic_string() << " to tutaj"<< std::endl;
		list.pushBack(window, blockPressed, listBlock, listBlock, clickBuff, switchBuff, font);
		list.setPosition(linex, liney + 50 + i * 50);
		list.setScale(1.8, 1);
		list.setText(entry.path().filename().generic_string());
		i++;
		if (i == 5)
			break;
	}
	list.setSoundVolume(setting.SoundVolume);
	list.chooseDefault();

	Button goBack(window, blockPressed, block, offButton, clickBuff, switchBuff, font);
	goBack.setPosition(linex, liney + 200 + 4 * 58);
	goBack.setScale(1.8, 1);
	goBack.setTitle("Back");
	goBack.setSoundVolume(setting.SoundVolume);


	Button musicApply(window, blockPressed, block, offButton, clickBuff, switchBuff, font);
	musicApply.setPosition(linex, liney + 100 + 4 * 58);
	musicApply.setScale(1.8, 1);
	musicApply.setTitle("apply");
	musicApply.setSoundVolume(setting.SoundVolume);
	
	bool alertFlag = false;
	double volume;
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (!alertFlag)
			{
				goBack.checkState();
				musicApply.checkState();
				musicSlider.checkState();
				soundSlider.checkState();
				list.checkState();
				if (musicApply.buttonFunction())
				{
					bool try_ = music.setGameMusic(list.getFileDirect());
					if (!try_)
					{
						alert.setText("nie udalo sie odczytac \npliku, moze uzyj spotify :)");
						alertFlag = true;
						musicApply.normalization();
						alert.show();
					}
				}
				else if (goBack.buttonFunction())
					return st::mainMenu;
				else if (musicSlider.sliderFunction(volume))
				{
					setting.MusicVolume = volume;
					music.setVolume(volume * 30);
				}
				else if (soundSlider.sliderFunction(volume))
				{
					setting.SoundVolume = volume;
					musicSlider.setSoundVolume(setting.SoundVolume);
					soundSlider.setSoundVolume(setting.SoundVolume);
					goBack.setSoundVolume(setting.SoundVolume);
					list.setSoundVolume(setting.SoundVolume);
					musicApply.setSoundVolume(setting.SoundVolume);
				}
				else;
			}
			else
			{
				alert.checkState();
				if (alert.function())
				{
					alertFlag = false;
					alert.hide();
				}
			}
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
		alert.draw();

		window.display();
	}
	return st::mainMenu;
}
st Menu::normalGameUpdate()
{
	int linex = window.getSize().x / 2 - 190 * 1.8 / 2;
	int liney = window.getSize().y / 2 - 50;

	sf::Event event;


	Button goBack(window, blockPressed, block, offButton, clickBuff, switchBuff, font);
	goBack.setPosition(linex, liney + 200 + 4 * 58);
	goBack.setScale(1.8, 1);
	goBack.setTitle("Back");
	goBack.setSoundVolume(setting.SoundVolume);


	Button play(window, blockPressed, block, offButton, clickBuff, switchBuff, font);
	play.setPosition(linex, liney + 100 + 4 * 58);
	play.setScale(1.8, 1);
	play.setTitle("play");
	play.setSoundVolume(setting.SoundVolume);

	/*inputText text(window, block, clickBuff);
	text.setSize(30);
	text.setColor(sf::Color::Black);
	text.setFont(font);
	text.setPosition(window.getSize().x / 2, window.getSize().y / 2);
	text.setScale(1.8, 1);
	text.defaultString("nickname");
	*/

	setPlayer::clearForbidden();
	
	setPlayer player1(window, nickNameOnBlue, nickNameOffBlue, controlOnBlue, controlOffBlue, checkOnBlue, checkOff,clickBuff, font);
	player1.setPosition(200, 200);
	player1.setSoundVolume(setting.SoundVolume);

	setPlayer player2(window, nickNameOnGreen, nickNameOffGreen, controlOnGreen, controlOffGreen, checkOnGreen, checkOff, clickBuff, font);
	player2.setPosition(500, 200);
	player2.setSoundVolume(setting.SoundVolume);

	setPlayer player3(window, nickNameOnYellow, nickNameOffYellow, controlOnYellow, controlOffYellow, checkOnYellow, checkOff, clickBuff, font);
	player3.setPosition(800, 200);
	player3.setSoundVolume(setting.SoundVolume);

	setPlayer player4(window, nickNameOnRed, nickNameOffRed, controlOnRed, controlOffRed, checkOnRed, checkOff, clickBuff, font);
	player4.setPosition(1100, 200);
	player4.setSoundVolume(setting.SoundVolume);

	setPlayer player5(window, nickNameOnBlue, nickNameOffBlue, controlOnBlue, controlOffBlue, checkOnBlue, checkOff, clickBuff, font);
	player5.setPosition(200, 500);
	player5.setSoundVolume(setting.SoundVolume);

	setPlayer player6(window, nickNameOnGreen, nickNameOffGreen, controlOnGreen, controlOffGreen, checkOnGreen, checkOff, clickBuff, font);
	player6.setPosition(500, 500);
	player6.setSoundVolume(setting.SoundVolume);

	setPlayer player7(window, nickNameOnYellow, nickNameOffYellow, controlOnYellow, controlOffYellow, checkOnYellow, checkOff, clickBuff, font);
	player7.setPosition(800, 500);
	player7.setSoundVolume(setting.SoundVolume);

	setPlayer player8(window, nickNameOnRed, nickNameOffRed, controlOnRed, controlOffRed, checkOnRed, checkOff, clickBuff, font);
	player8.setPosition(1100, 500);
	player8.setSoundVolume(setting.SoundVolume);

	setPlayer* activated = &player1;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			//text.checkState();
			goBack.checkState();
			play.checkState();
			player1.checkState();
			player2.checkState();
			player3.checkState();
			player4.checkState();
			player5.checkState();
			player6.checkState();
			player7.checkState();
			player8.checkState();
			if (setPlayer::getFocus() && event.type == sf::Event::KeyPressed)
			{
				activated->setChar(event.key.code);
			}
			//else if (text2.getFocuse() && event.type == sf::Event::TextEntered)
				//text2.addChar(event.text.unicode);

				if (goBack.buttonFunction())
					return st::mainMenu;
				else if (play.buttonFunction())
				{
					;
				}
				else if (player1.function())
				{
					activated = &player1;
				}
				else if (player2.function())
				{
					activated = &player2;
				}
				else if (player3.function())
				{
					activated = &player3;
				}
				else if (player4.function())
				{
					activated = &player4;
				}
				else if (player5.function())
				{
					activated = &player5;
				}
				else if (player6.function())
				{
					activated = &player6;
				}
				else if (player7.function())
				{
					activated = &player7;
				}
				else if (player8.function())
				{
					activated = &player8;
				}
				
				//else if (text2.function())
				//{
				//	activatedt = &text2;
				//}

		}
		window.clear(sf::Color::Black);

		background.draw();

		goBack.draw();
		play.draw();
		//text.draw();
		//text2.draw();
		player1.draw();
		player2.draw();
		player3.draw();
		player4.draw();
		player5.draw();
		player6.draw();
		player7.draw();
		player8.draw();
		window.display();
	}
}
Menu::~Menu()
{
}
