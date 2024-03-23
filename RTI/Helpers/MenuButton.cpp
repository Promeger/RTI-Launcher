#include "MenuButton.h"
#include "GlobalFont.h"

#include <iostream>

MenuButton::MenuButton()
{

}

MenuButton::MenuButton(std::string label, std::string iconPath, std::function<void()> action)
{
    init(label, iconPath, action);
}

void MenuButton::init(std::string label, std::string iconPath, std::function<void()> action)
{
    m_iconTx.loadFromFile(iconPath);
    m_icon.setTexture(m_iconTx);
    m_label.setFont(*GlobalFont::get()->getFont());
    m_label.setString(label);
    m_label.setCharacterSize(20);
    m_label.setStyle(sf::Text::Bold);

    m_action = action;

}

void MenuButton::setPosition(int x, int y)
{
    m_icon.setPosition(x, y);
    m_label.setPosition(m_icon.getGlobalBounds().left + m_icon.getGlobalBounds().width / 2.f - (m_label.getGlobalBounds().width / 2.f), y + 110);
}

void MenuButton::process(sf::RenderWindow& window)
{
    if (m_icon.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
    {
        m_action();
    }

}

void MenuButton::draw(sf::RenderWindow& window)
{

    window.draw(m_icon);
    window.draw(m_label);
}