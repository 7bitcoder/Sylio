#include "players.h"

players::players(std::array<std::array<int, 1920>, 1080>& hitbox_,sf::RenderWindow& win, int & ymax_, int & ymin_, int & xmax_, int & xmin_, int& thicc_, sf::RenderTexture& board_)
	:window(win), 
	hitbox(hitbox_),
	board(board_),
	ymax(ymax_),
	xmax(xmax_),
	xmin(xmin_),
	ymin(ymin_),
	thicc(thicc_)
{

	thicc = 5;
	int i = 1;
	 for(auto& x : setting.playersSettings)
	{
		Players.push_back(std::move(Player(hitbox ,window, x.color, ymax, ymin, xmax, xmin, board)));
		Players.back().setParams(0, 2, 2.5, 100);
		Players.back().setId(i);
		Players.back().setControls(x.left, x.right);
		Players.back().setPosition(600 + i * 200, 100);
		Players.back().setNick(x.nickname);
		i++;
		Players.back().setGapBounds(40, 300, 500, 1000);
	}
	/*
		Players.push_back(std::move(Player(hitbox ,window, sf::Color::Red, ymax, ymin, xmax, xmin, board)));
		Players.back().setParams(0, 25, 2.5, 100);
		Players.back().setId(i);
		Players.back().setControls(sf::Keyboard::Key::S, sf::Keyboard::Key::D);
		Players.back().setPosition(600 + i * 200, 100);
		Players.back().setNick("sylwow");
		i++;
		allHeadRadious.push_back(5);
		Players.back().setGapBounds(40, 300, 500, 1000);*/
}



players::~players()
{
}

