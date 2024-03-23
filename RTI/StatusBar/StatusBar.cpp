
#include "StatusBar.h"
#include "../Helpers/GlobalFont.h"
#include "../Helpers/CurrentApp.h"

StatusBar::StatusBar(GlobalState* state)
{
	init(state);
}

void StatusBar::init(GlobalState* state)
{
	m_bar.setFillColor(sf::Color(0, 0, 0, 255));
	m_bar.setSize(sf::Vector2f(800.f, 40.f));
	m_bar.setPosition(0.f, 0.f);

	m_appTitle.setFont(*GlobalFont::get()->getFont());
	m_appTitle.setFillColor(sf::Color(255, 255, 255, 255));
	m_appTitle.setString("Undefined");
	m_appTitle.setCharacterSize(20);
	m_appTitle.setPosition(sf::Vector2f(50.f, 8.f));

	m_clock.setFont(*GlobalFont::get()->getFont());
	m_clock.setFillColor(sf::Color(255, 255, 255, 255));
	m_clock.setString("00:00");
	m_clock.setCharacterSize(20);
	m_clock.setPosition(sf::Vector2f(740.f, 8.f));

	m_homeTexture.loadFromFile("Media/icons/system/home.png");
	m_homeButton.setTexture(m_homeTexture);

	m_state = state;

}

void StatusBar::draw(sf::RenderWindow& window)
{
	window.draw(m_bar);
	window.draw(m_homeButton);
	window.draw(m_appTitle);
	window.draw(m_clock);
}

void StatusBar::processClick(sf::RenderWindow& window)
{

	if (m_homeButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
	{
		CurrentApp::set(NULL);

		if(m_state)
			*m_state = Menu;
	}
}

void StatusBar::update(sf::RenderWindow& window)
{
	std::time_t t = std::time(0); 
	std::tm* now = std::localtime(&t);
	m_clock.setString((now->tm_hour < 10 ? "0" : "" ) + std::to_string(now->tm_hour) + ":" + (now->tm_min < 10 ? "0" : "") + std::to_string(now->tm_min));
}

void StatusBar::setTitle(std::string title)
{
	m_appTitle.setString(title); 
}