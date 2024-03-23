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
	void ff();
	void rewind();
	void next();
	void prev();

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
	void invalidateBrowser();


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
	struct BrowserEntry
	{
		sf::Text text;
		sf::Sprite* icon = NULL;
		sf::RectangleShape addToPlist;
		std::pair<int, std::pair<std::wstring, std::wstring>> browserData;
	};

	sf::RectangleShape m_browserDivider;
	sf::RectangleShape m_browserButtons[3];
	unsigned int m_brIndex;
	unsigned int m_brMaxIndex;

	std::wstring m_brCurrentPath;
	std::vector<std::pair<int, std::pair<std::wstring, std::wstring>>> m_brData;

	std::vector<BrowserEntry> m_brCurrentEntries;
	sf::Texture m_brFileTexture;
	sf::Texture m_brFolderTexture;


	const static std::vector<std::string> s_brExtensions;

	


	//Playlist
};