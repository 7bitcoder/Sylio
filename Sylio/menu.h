#include<SFML/Graphics.hpp>
#include<string>
class Menu
{
private:
	sf::RenderWindow& window;
	std::string & version;
	bool isOnButton(sf::Sprite&);
	bool isAlredyOnButton(sf::Sprite&);
	
public:
	Menu(sf::RenderWindow& win, std::string &ver) : window(win), version(ver) {};
	int update();
	~Menu();
};

