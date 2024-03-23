#include "GlobalFont.h"
#include <iostream>

GlobalFont* GlobalFont::s_instance = NULL;

GlobalFont::GlobalFont()
{
	m_font = new sf::Font();
	if (!m_font->loadFromFile("Media/fonts/roboto.ttf"))
	{
		std::cerr << "Error Loading Font" << std::endl;
	}
}

GlobalFont* GlobalFont::get()
{
	if (!s_instance)
		s_instance = new GlobalFont();

	return s_instance;
}

sf::Font* GlobalFont::getFont() 
{
	return m_font;
}