#include "MainMenu.h"
#include "../Helpers/GlobalFont.h"
#include "../Helpers/CurrentApp.h"

#include "../Settings/Settings.h"
#include "../Player/Player.h"


#include <iostream>

MainMenu::MainMenu(GlobalState* globalState, StatusBar* statusBar)
{
	init(globalState, statusBar);
}

void MainMenu::init(GlobalState* globalState, StatusBar* statusBar)
{
    m_state = globalState;
    m_statusBar = statusBar;

    m_apps = new Application*[3];
    m_apps[2] = new Settings();
    m_apps[2]->init();
    m_apps[1] = new Player();
    m_apps[1]->init();

    m_mmClock.setFont(*GlobalFont::get()->getFont());
    m_mmClock.setFillColor(sf::Color::White);
    m_mmClock.setString("00:00");
    m_mmClock.setCharacterSize(100);
    m_mmClock.setPosition(80, 100);

    m_mmText.setFont(*GlobalFont::get()->getFont());
    m_mmText.setFillColor(sf::Color::White);
    m_mmText.setString("No new notifications");
    m_mmText.setCharacterSize(20);
    m_mmText.setPosition(90, 220);
    m_mmText.setStyle(sf::Text::Bold);


    m_buttons[0].init("CarPlay", "Media/icons/carplay.png", []() { system("sudo ./carplay/carplay"); });
    m_buttons[1].init("Music", "Media/icons/music.png", [&]() { changeApp(m_apps[1]); });
    m_buttons[2].init("Settings", "Media/icons/settings.png", [&]() { changeApp(m_apps[2]); });

    const int starterTmplX = 360;
    const int starterTmplY = 20;


    for (int i = 0; i < 3; i++)
    {
        m_buttons[i].setPosition(starterTmplX + 110 * (i % 4), starterTmplY + 130 * (i / 4));

    }

    if (!m_wallpaperTx.loadFromFile("Media/wallpaper.jpg"))
    {
        // error...
    }

    m_wallpaper.setTexture(m_wallpaperTx);
}

void MainMenu::processClick(sf::RenderWindow& window)
{
    for (int i = 0; i < 3; i++)
    {
        m_buttons[i].process(window);
    }
}

void MainMenu::draw(sf::RenderWindow& window)
{
    window.draw(m_wallpaper);

    for (int i = 0; i < 3; i++)
    {
        m_buttons[i].draw(window);
    }
    std::time_t t = std::time(0);   // get time now
    std::tm* now = std::localtime(&t);
    m_mmClock.setString((now->tm_hour < 10 ? "0" : "") + std::to_string(now->tm_hour) + ":" + (now->tm_min < 10 ? "0" : "") + std::to_string(now->tm_min));
    window.draw(m_mmClock);
    window.draw(m_mmText);
}

void MainMenu::changeApp(Application* app)
{
    CurrentApp::set(app);
    m_statusBar->setTitle(app->getTitle());
    *m_state = App;
}
