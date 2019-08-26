# Sylio
Sylio is simple multiplayer game, up to eight players controls snail and tries to survive as long as it is possible.
## Getting Started
Currently application works only on windows and the best screen resolution is fullHd

If you find any bugs leave feedback
## Screenshots
![main menu](ScreenShots/mainMenu.png)
![setup game](ScreenShots/setUpGame.png)
![gameplay](ScreenShots/inGame.png)
![gameplay2](ScreenShots/inGame3.jpg)
![gameplay3](ScreenShots/inGame4.jpg)
## Instalator
link to instalator :

https://drive.google.com/drive/folders/1VCkCfbHeYCj8A6g9C8OCWWS_vs863Ih-?usp=sharing

If sylio.exe did not installed properly copy file from link above and paste to YourDir/Release
## Game Description
soon
## Game Rules 
* Players die when snail head collide with snail tails or gameboard bounds.
* Round is over when only last player is still alive
* Player score is update when: player dies or round is over
* Points function: points gained for current round = dead players + player segments (visible on board)
* Powerups:
* <img src="boost_icons/speed_up.png" width="25">  speed up: increases speed by 20%
* <img src="boost_icons/slow_down.png" width="25">  slow down: decreases speed by 20%
* <img src="boost_icons/blind.png" width="25">  blind: make tails invisible
* <img src="boost_icons/freeze.png" width="25">  freeze: freezes player for 5s
* <img src="boost_icons/grow_up.png" width="25">  grow up: increase radious by 20%
* <img src="boost_icons/shrink.png" width="25">  shrink: decreases radious by 20%
* <img src="boost_icons/only_left.png" width="25">  lock left: lock left turns
* <img src="boost_icons/only_left2.png" width="25">  lock right: lock right turns
* <img src="boost_icons/switch_controls.png" width="25">  switch controls: switch controls of your snake
* <img src="boost_icons/immortal.png" width="25">  immortal: you are immortal (accept when crossing bounds)
* <img src="boost_icons/broken_walls.png" width="25">  broken walls: you can cross gameboard bounds
* <img src="boost_icons/longer_gaps.png" width="25">  longer gaps: increase your gaps by 20%
* <img src="boost_icons/more_often_holes.png" width="25">  chese: your snake makes gaps more often by 20%
* <img src="boost_icons/bounds.png" width="25">  collapse: walls are collapsing for a while

* Powerups are spawning on board every 10 - 20 sec (random) and default duration is 5s
* Each powerup can be spawned in 4 colours :
-- white: powerup affects all players
-- green: powerup affects only player that activated boost
-- red: powerup affects all player except one that activated boost
-- yellow: powerup affects random player
* Note that each powerup don't have to appear in all of 4 colours, some of them are negative (only red) etc.
## Music
Music creator: Bartosz Twardy

https://soundcloud.com/bartosz-twardy-111728082?fbclid=IwAR0gtAkXr3lYFIJDBXkoVPhbxdpg4p6mamCXlR8p2_QWc7UPwoeV9wzrHgo
## Built With
* [Sfml](https://www.sfml-dev.org/) - multi-platform media library
## Authors
***Sylwow***
## License
This project is licensed under the MIT License - see the [LICENSE.md](license.txt) file for details
