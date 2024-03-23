#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <string>


class MenuButton
{
public:
	MenuButton();
	MenuButton(std::string label, std::string iconPath, std::function<void()> action);
	void init(std::string label, std::string iconPath, std::function<void()> action); 
	void setPosition(int x, int y);

	void process(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);

private:
	sf::Texture m_iconTx;
	sf::Sprite m_icon;
	sf::Text m_label;
	std::function<void()> m_action;
};