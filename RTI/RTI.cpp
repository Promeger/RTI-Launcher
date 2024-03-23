// RTI.cpp : Defines the entry point for the application.
//

#include "RTI.h"

#include <SFML/Graphics.hpp>

#include "Helpers/GlobalState.h"
#include "Helpers/CurrentApp.h"
#include "StatusBar/StatusBar.h"
#include "MainMenu/MainMenu.h"


const bool isProd = false;

GlobalState globalState = GlobalState::Menu;
StatusBar statusbar(&globalState);
MainMenu* menu = NULL;




int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 480), "RTI", isProd ? sf::Style::Fullscreen : sf::Style::Default);

    menu = new MainMenu(&globalState, &statusbar);

    while (window.isOpen())
    {
        window.clear();


        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                if (globalState == GlobalState::Menu)
                { 
                    menu->processClick(window);
                }
                else
                {

                    statusbar.processClick(window);

                    auto currentApp = CurrentApp::get();
                    if(currentApp)
                        currentApp->processClick(window);
                }

               
            }
        }


        if (globalState == GlobalState::Menu)
        {
            menu->draw(window);
        }
        else
        {
            statusbar.update(window);

            auto currentApp = CurrentApp::get();

            if (currentApp)
                currentApp->draw(window);

            statusbar.draw(window);
        }



        window.display();
    }

    return 0;
}