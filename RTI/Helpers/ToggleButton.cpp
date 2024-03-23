#include "ToggleButton.h"
#include "GlobalFont.h"

int selectedColor = 192;
int unselectedColor = 16;

ToggleButton::ToggleButton(int x, int y, bool value) : m_x(x), m_y(y), m_value(value)
{
	m_bg.setFillColor(sf::Color((value ? selectedColor : unselectedColor), (value ? selectedColor : unselectedColor), (value ? selectedColor : unselectedColor), 255));
	m_bg.setSize(sf::Vector2f(50.f, 25));
	m_bg.setPosition(x, y);

	m_text.setFont(*GlobalFont::get()->getFont());
	m_text.setFillColor(sf::Color((value ? 0 : 255), (value ? 0 : 255), (value ? 0 : 255), 255));
	m_text.setString((value ? "ON" : "OFF"));
	m_text.setCharacterSize(20);
	auto qNS = m_text.getLocalBounds();
	m_text.setPosition(sf::Vector2f(x + 25.f - qNS.width / 2.f, y - 12.5f - qNS.height / 2.f));
	auto tPos = m_text.getGlobalBounds();
	m_bg.setPosition((tPos.left + (tPos.width / 2)) - 25.f, (tPos.top + (tPos.height / 2)) - 12.5f);
}

void ToggleButton::processClick(sf::RenderWindow& window)
{
	auto pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

	if (m_bg.getGlobalBounds().contains(pos))
	{
		setValue(!getValue());
	}
}

bool ToggleButton::getValue()
{
	return m_value;
}

void ToggleButton::setValue(bool value)
{
	m_value = value;
	m_bg.setFillColor(sf::Color((value ? selectedColor : unselectedColor), (value ? selectedColor : unselectedColor), (value ? selectedColor : unselectedColor), 255));
	m_text.setFillColor(sf::Color((value ? 0 : 255), (value ? 0 : 255), (value ? 0 : 255), 255));
	m_text.setString((value ? "ON" : "OFF"));
	auto qNS = m_text.getLocalBounds();
	m_text.setPosition(sf::Vector2f(m_x + 25.f - qNS.width / 2.f, m_y - 12.5f - qNS.height / 2.f));
	auto tPos = m_text.getGlobalBounds();

	m_bg.setPosition((tPos.left + (tPos.width / 2)) - 25.f, (tPos.top + (tPos.height / 2)) - 12.5f);

}

void ToggleButton::draw(sf::RenderWindow& window)
{
	window.draw(m_bg);
	window.draw(m_text);
}