#pragma once
#include <SFML/Graphics.hpp>

class Application
{
public:
	Application();
	virtual void init() = 0;

	std::string getTitle();
	
	virtual void processClick(sf::RenderWindow& window) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
protected:
	std::string m_appTitle;
};