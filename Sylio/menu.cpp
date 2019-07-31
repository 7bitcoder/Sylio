#include "menu.h"

Menu::Menu(sf::RenderWindow& win, std::string& ver_): window(win), version(ver_), background(win)
{

	if (!clickBuff.loadFromFile("../Sounds/click1.ogg"))
		exit(-1);

	if (!switchBuff.loadFromFile("../Sounds/switch2.ogg"))
		exit(-1);

	if (!font2.loadFromFile("../Font/kenvector_future_thin.ttf"))
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
	//back.setSmooth(true);

	if (!whiteBox.loadFromFile("../PNG/grey_panel.png"))
		exit(-1);

	if (!base.loadFromFile("../base3.png"))
		exit(-1);

	if (!mar.loadFromFile("../PNG/grey_sliderRight.png"))
		exit(-1);

	if (!VolumeSliderLine.loadFromFile("../PNG/grey_sliderHorizontal.png"))
		exit(-1);

	if (!VolumePointner.loadFromFile("../PNG/grey_sliderUp.png"))
		exit(-1);

	if (!listBlock.loadFromFile("../PNG/grey_button06.png"))
		exit(-1);

	if (!backgroundShader.loadFromFile("../shaders/shaders/fragment/material-specular.frag", sf::Shader::Fragment))
		exit(-1);

	background.setShader(backgroundShader);
	background.set(back, base, 0, 0.002);

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
				else if (musicSlider.sliderFunction())
				{
					setting.MusicVolume = musicSlider.getValue();
					music.setVolume(musicSlider.getValue() * 30);
				}
				else if (soundSlider.sliderFunction())
				{
					setting.SoundVolume = soundSlider.getValue();
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
	setting.playersSettings.clear();

	PopAlert alert(window, "asdasd", whiteBox, blockPressed, block, offButton, clickBuff, switchBuff, font2);

	int linex = window.getSize().x / 2 - 190 * 1.8 / 2;
	int liney = window.getSize().y / 2 - 50;

	sf::Event event;


	Button goBack(window, blockPressed, block, offButton, clickBuff, switchBuff, font);
	goBack.setPosition(linex, liney + 300);
	goBack.setScale(1.8, 1);
	goBack.setTitle("Back");
	goBack.setSoundVolume(setting.SoundVolume);


	Button play(window, blockPressed, block, offButton, clickBuff, switchBuff, font);
	play.setPosition(linex, liney + 200);
	play.setScale(1.8, 1);
	play.setTitle("play");
	play.setSoundVolume(setting.SoundVolume);
	
	Rounds rounds(window, controlOnBlue, controlOffBlue, VolumePointner, VolumeSliderLine, clickBuff);
	rounds.setFont(font);
	rounds.setBoxPosition(linex+100, 300);
	rounds.setSliderPosition(linex , 500 - 30);
	rounds.setScale(2.5, 2.5);
	rounds.setSize(60);
	rounds.setTextPosition(linex + 120, 300 + 20);
	rounds.setSoundVolume(setting.SoundVolume);
	rounds.setString("");
	rounds.addNumber('2');
	rounds.addNumber('0');
	rounds.setColor(sf::Color::Black);

	std::cout << rounds.addNumber(10);
	
	setPlayer::clearForbidden();
	int row = 90 ;
	int off = 100;
	int col = 150;

	std::vector<setPlayer> players;
	players.push_back(std::move(setPlayer(window, nickNameOnBlue, nickNameOffBlue, controlOnBlue, controlOffBlue, checkOnBlue, checkOff, clickBuff, font2, "player1")));
	players.back().setPosition(col, row + off);
	players.back().setSoundVolume(setting.SoundVolume);
	players.back().setColor(sf::Color(53,186,243,255));

	players.push_back(std::move(setPlayer(window, nickNameOnGreen, nickNameOffGreen, controlOnGreen, controlOffGreen, checkOnGreen, checkOff, clickBuff, font2, "player2")));
	players.back().setPosition(col, row*2 + off);
	players.back().setSoundVolume(setting.SoundVolume);
	players.back().setColor(sf::Color(136,224,96,255));

	players.push_back(std::move(setPlayer (window, nickNameOnYellow, nickNameOffYellow, controlOnYellow, controlOffYellow, checkOnYellow, checkOff, clickBuff, font2, "player3")));
	players.back().setPosition(col, row*3 + off);
	players.back().setSoundVolume(setting.SoundVolume);
	players.back().setColor(sf::Color(255,217,72,255));

	players.push_back(std::move(setPlayer (window, nickNameOnRed, nickNameOffRed, controlOnRed, controlOffRed, checkOnRed, checkOff, clickBuff, font2, "player4")));
	players.back().setPosition(col, row*4 + off);
	players.back().setSoundVolume(setting.SoundVolume);
	players.back().setColor(sf::Color(250,129,50,255));

	players.push_back(std::move(setPlayer (window, nickNameOnBlue, nickNameOffBlue, controlOnBlue, controlOffBlue, checkOnBlue, checkOff, clickBuff, font2, "player5")));
	players.back().setPosition(col, row*5 + off);
	players.back().setSoundVolume(setting.SoundVolume);
	players.back().setColor(sf::Color::Red);

	players.push_back(std::move(setPlayer (window, nickNameOnGreen, nickNameOffGreen, controlOnGreen, controlOffGreen, checkOnGreen, checkOff, clickBuff, font2, "player6")));
	players.back().setPosition(col, row*6 + off);
	players.back().setSoundVolume(setting.SoundVolume);
	players.back().setColor(sf::Color::Red);

	players.push_back(std::move(setPlayer (window, nickNameOnYellow, nickNameOffYellow, controlOnYellow, controlOffYellow, checkOnYellow, checkOff, clickBuff, font2, "player7")));
	players.back().setPosition(col, row*7 + off);
	players.back().setSoundVolume(setting.SoundVolume);
	players.back().setColor(sf::Color::Red);

	players.push_back(std::move(setPlayer (window, nickNameOnRed, nickNameOffRed, controlOnRed, controlOffRed, checkOnRed, checkOff, clickBuff, font2, "player8")));
	players.back().setPosition(col, row*8 + off);
	players.back().setSoundVolume(setting.SoundVolume);
	players.back().setColor(sf::Color::Red);

	setPlayer* activated = &players[0];
	bool alertFlag = false;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (!alertFlag)
			{
				goBack.checkState();
				play.checkState();
				players[1].checkState();
				players[2].checkState();
				players[3].checkState();
				players[4].checkState();
				players[5].checkState();
				players[6].checkState();
				players[7].checkState();
				players[0].checkState();
				rounds.checkState();
				if (setPlayer::getFocus() && event.type == sf::Event::KeyPressed)
				{
					activated->setChar(event.key.code);
				}
				if (rounds.getFocuse())
				{
					if (event.type == sf::Event::TextEntered)
					{
						rounds.addNumber(static_cast<char>(event.text.unicode));
					}
					else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
					{
						rounds.updateText();
						rounds.disActivate();
					}
				}
				if (goBack.buttonFunction())
					return st::mainMenu;
				else if (play.buttonFunction())
				{
					bool empty = false;
					bool emptyControlls = false;
					for (auto& player : players)
					{
						if (player.getActive())
						{
							std::string str = player.getNickname();
							sf::Keyboard::Key right = player.getRightKey();
							sf::Keyboard::Key left = player.getLeftKey();
							sf::Color color = player.getColor();
							if (str.empty() || right == sf::Keyboard::Unknown || left == sf::Keyboard::Unknown)
							{
								if (str.empty())
									empty = true;
								if (right == sf::Keyboard::Unknown || left == sf::Keyboard::Unknown)
									emptyControlls = true;
								break;
							}
							setting.playersSettings.push_back({ color, str, left, right });
						}
					}
					if (setting.playersSettings.size() < 2 || empty || emptyControlls)
					{
						std::string msg;
						if (setting.playersSettings.size() < 2) msg += "minimum two players required \nto start the game\n";
						if(empty)  msg += "you didn't choose your nickname\n";
						if (emptyControlls) msg += "you didn't choose your controls\n";
						alert.setText(msg);
						alertFlag = true;
						alert.show();
						setting.playersSettings.clear();
					}
					else
						return st::playNormalGame;
						/*for (auto& x : setting.playersSettings)
					{
						std::cout << x.nickname << "  hh " << int(x.left) << "  hh " << int(x.right) << "\n\n";
					}*/
					
				}
				else if (players[1].function())
				{
					activated = &players[1];
				}
				else if (players[2].function())
				{
					activated = &players[2];
				}
				else if (players[3].function())
				{
					activated = &players[3];
				}
				else if (players[4].function())
				{
					activated = &players[4];
				}
				else if (players[5].function())
				{
					activated = &players[5];
				}
				else if (players[6].function())
				{
					activated = &players[6];
				}
				else if (players[7].function())
				{
					activated = &players[7];
				}
				else if (players[0].function())
				{
					activated = &players[0];
				}
				else if (rounds.function());
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
		play.draw();
		for (auto& x : players)
			x.draw();
		rounds.draw();
		alert.draw();
		window.display();
	}
}
Menu::~Menu()
{
}
