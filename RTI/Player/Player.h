#pragma once

#include "../Helpers/Application.h"
#include "../Helpers/Slider.h"
#include "../Helpers/ToggleButton.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


class Player : public Application
{
public:
	Player();
	void init();

	void processClick(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);

	bool openFile(std::string path);

	void play();
	void pause();

	enum PlayerState
	{
		MainScreen,
		Browsing,
		Playlist
	};

	enum PlaySate
	{
		Playing,
		Paused
	};

private:
	

	void refreshBrowser();


	PlayerState m_playerState;
	PlaySate m_playState;
	
	sf::Music m_musicFile;
	std::string m_currentFilePath;
	
	std::wstring m_currentTitle;
	std::wstring m_currentArtist;
	std::wstring m_currentAlbum;

	sf::RectangleShape m_bg;
	sf::RectangleShape m_buttons[8];

	sf::Texture m_coverTexture;
	sf::Texture m_transportTexture;
	sf::Sprite m_cover;
	Slider m_progress;
	sf::Text m_title;
	sf::Text m_artist;
	sf::Text m_album;
	sf::Text m_info;
	sf::Text m_audioPosition;


	//Browser
	std::wstring m_brCurrentPath;


	

	//Texts
};