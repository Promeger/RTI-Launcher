#pragma once

#include "../Helpers/Application.h"
#include "../Helpers/Slider.h"
#include "../Helpers/ToggleButton.h"

#include <SFML/Graphics.hpp>


class Settings : public Application
{
public:
	Settings();
	void init();

	void processClick(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);


	enum SettingsState
	{
		None = -1,
		Audio = 0,
		Display = 1,
		Information = 2,
		Debug = 3,
		ExitToX = 4,
		ShutDown = 5
	};


private:
	void renderMenuElements(sf::RenderWindow& window);
	void renderSubMenuElements(sf::RenderWindow& window);

	struct MenuData
	{
		sf::Text text;
		sf::Texture* iconTx = NULL;
		sf::Sprite* icon = NULL;
		SettingsState state;
	};


	sf::RectangleShape m_leftMenuShape;
	SettingsState m_internalState;
	std::vector<MenuData> m_mainMenuItems;
	std::vector<sf::Text> m_infoScreenA;
	std::vector<sf::Text> m_infoScreenB;
	std::vector<sf::Text> m_audioTitles;
	std::vector<sf::Text> m_displayTitles;
	sf::RectangleShape m_lineDividerSM;
	sf::RectangleShape m_lineDividerMM;

	sf::Text m_question;
	sf::Text m_questionY;
	sf::Text m_questionN;
	sf::RectangleShape m_questionYBtn;
	sf::RectangleShape m_questionNBtn;
	Slider m_volumeSlider;
	Slider m_brightnessSlider;
	ToggleButton m_externalAudioTB;
	ToggleButton m_darkmodeTB;
};