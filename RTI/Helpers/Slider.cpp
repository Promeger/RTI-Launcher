#include "Slider.h"
#include "GlobalFont.h"

Slider::Slider(int x, int y, int min, int max, int value, int length, bool renderTexts) : m_xCord(x), m_yCord(y), m_axisWidth(length), m_renderTexts(renderTexts)
{
	m_axisHeight = 5;
	m_sliderWidth = 20;
	m_sliderHeight = 25;

	m_text.setFont(*GlobalFont::get()->getFont());
	m_text.setFillColor(sf::Color::White);

	m_axis.setPosition(x, y);
	m_axis.setOrigin(0, m_axisHeight / 2);
	m_axis.setSize(sf::Vector2f(m_axisWidth, m_axisHeight));
	m_axis.setFillColor(sf::Color(63, 63, 63));
	m_slider.setPosition(x, y);
	m_slider.setOrigin(m_sliderWidth / 2, m_sliderHeight / 2);
	m_slider.setSize(sf::Vector2f(m_sliderWidth, m_sliderHeight));
	m_slider.setFillColor(sf::Color(192, 192, 192));

	m_sliderValue = (value > min ? (value < max ? value : max) : min);
	m_minValue = min;
	m_maxValue = max;
}

bool Slider::processClick(sf::RenderWindow& window)
{
	auto pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	if (pos.x >= m_xCord && pos.x <= m_xCord + m_axisWidth && pos.y >= m_yCord - (m_sliderHeight / 2.f) && pos.y <= m_yCord + (m_sliderHeight / 2.f))
	{
		m_slider.setPosition(pos.x, m_yCord);
		m_sliderValue = (int)(m_minValue + ((m_slider.getPosition().x - m_xCord) / m_axisWidth * (m_maxValue - m_minValue)));
		return true;
	}

	return false;
}

int Slider::getValue()
{
	return m_sliderValue;
}

void Slider::setValue(int newValue)
{
	if (newValue >= m_minValue && newValue <= m_maxValue)
	{
		m_sliderValue = newValue;
		float diff = m_maxValue - m_minValue;
		float diff2 = newValue - m_minValue;
		float zzz = m_axisWidth / diff;
		float posX = zzz * diff2;
		posX += m_xCord;
		m_slider.setPosition(posX, m_yCord);
	}

	m_sliderValue = newValue;
}

void Slider::setPercentValue(int newPercentValue)
{
	if (newPercentValue >= 0 && newPercentValue <= 100)
	{
		m_sliderValue = newPercentValue / 100 * m_maxValue;
		m_slider.setPosition(m_xCord + (m_axisWidth * newPercentValue / 100), m_yCord);
	}
}

void Slider::draw(sf::RenderWindow& window)
{

	if(m_renderTexts)
		window.draw(returnText(m_xCord - 10, m_yCord + 5, std::to_string(m_minValue), 20));
	window.draw(m_axis);
	if (m_renderTexts)
		window.draw(returnText(m_xCord + m_axisWidth - 10, m_yCord + 5, std::to_string(m_maxValue), 20));
	window.draw(m_slider);
	if (m_renderTexts)
		window.draw(returnText(m_slider.getPosition().x - m_sliderWidth, m_slider.getPosition().y - m_sliderHeight, std::to_string((int)m_sliderValue), 15));
}

sf::Text Slider::returnText(int x, int y, std::string z, int fontSize)
{
	m_text.setCharacterSize(fontSize);
	m_text.setPosition(x, y);
	m_text.setString(z);
	return m_text;
}
