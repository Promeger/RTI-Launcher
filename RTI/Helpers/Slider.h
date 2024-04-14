#pragma once
#include <SFML/Graphics.hpp>

class Slider
{
public:
	Slider(int x, int y, int min, int max, int value = 0, int length = 100, bool renderTexts = true);
	bool processClick(sf::RenderWindow& window);
	int getValue();
	void setValue(int newValue);
	void setPercentValue(int newPercentValue);
	void draw(sf::RenderWindow& window);

private:

	sf::Text returnText(int x, int y, std::string z, int fontSize);

	sf::RectangleShape m_slider;
	sf::RectangleShape m_axis;
	sf::Text m_text;
	int m_minValue;
	int m_maxValue;
	int m_xCord;
	int m_yCord;
	int m_axisWidth;
	int m_axisHeight;
	int m_sliderWidth;
	int m_sliderHeight;
	int m_sliderValue;
	bool m_renderTexts;

};