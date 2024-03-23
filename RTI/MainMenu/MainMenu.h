#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <map>

#include "../Helpers/MenuButton.h"
#include "../Helpers/Application.h"
#include "../Helpers/GlobalState.h"
#include "../StatusBar/StatusBar.h"

class MainMenu
{
public:
	MainMenu(GlobalState* globalState, StatusBar* statusBar);
	void init(GlobalState* globalState, StatusBar* statusBar);

	void processClick(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);

private:
	void changeApp(Application* app);
	sf::Texture m_wallpaperTx;
	sf::Sprite m_wallpaper;
	sf::Text m_mmClock;
	sf::Text m_mmText;
	MenuButton m_buttons[3];
	Application** m_apps;
	GlobalState* m_state;
	StatusBar* m_statusBar;
};
