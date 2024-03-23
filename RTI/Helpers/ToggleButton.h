#pragma once
#include <SFML/Graphics.hpp>

class ToggleButton
{
public:
	ToggleButton(int x, int y, bool value = true);
	void processClick(sf::RenderWindow& window);
	bool getValue();
	void setValue(bool value);
	void draw(sf::RenderWindow& window);

private:

	sf::Text m_text;
	sf::RectangleShape m_bg;

	int m_x;
	int m_y;
	bool m_value;

};