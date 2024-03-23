#pragma once
#include <SFML/Graphics.hpp>

#include "../Helpers/GlobalState.h"

class StatusBar
{
public:
	StatusBar(GlobalState* state = NULL);
	void init(GlobalState* state);

	void draw(sf::RenderWindow& window);
	void processClick(sf::RenderWindow& window);
	void update(sf::RenderWindow& window);
	void setTitle(std::string title);


private:
	sf::RectangleShape m_bar;
	sf::Texture m_homeTexture;
	sf::Sprite m_homeButton;
	sf::Text m_appTitle;
	sf::Text m_clock;
	GlobalState* m_state;

};
