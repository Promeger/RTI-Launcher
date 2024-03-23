#include "Player.h"

#include "../Helpers/GlobalFont.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <taglib/fileref.h>
#include <taglib/tag.h>

Player::Player() : m_progress(40, 340, 0, 100, 100, 720, false), m_playerState(MainScreen), m_playState(Paused), m_currentFilePath(""), m_brCurrentPath(L"/")
{
	m_appTitle = "Music";
	init();
}

void Player::init()
{
	m_bg.setFillColor(sf::Color(32, 32, 32, 255));
	m_bg.setSize(sf::Vector2f(800.f, 440.f));
	m_bg.setPosition(0.f, 40.f);

	if (!m_coverTexture.loadFromFile("Media/icons/player/cover.png"))
	{
		// error...
	}

	m_cover.setTexture(m_coverTexture);

	if (!m_transportTexture.loadFromFile("Media/icons/player/transport.png"))
	{
		// error...
	}



	m_cover.setPosition(20.f, 60.f);


	m_title.setFont(*GlobalFont::get()->getFont());
	m_title.setFillColor(sf::Color(255, 255, 255, 255));
	m_title.setCharacterSize(40);
	m_title.setString("Title");
	m_title.setPosition(280.f, 60.f);

	m_artist.setFont(*GlobalFont::get()->getFont());
	m_artist.setFillColor(sf::Color(255, 255, 255, 255));
	m_artist.setCharacterSize(25);
	m_artist.setString("Artist");
	m_artist.setPosition(280.f, 120.f);

	m_album.setFont(*GlobalFont::get()->getFont());
	m_album.setFillColor(sf::Color(255, 255, 255, 255));
	m_album.setCharacterSize(25);
	m_album.setString("Album");
	m_album.setPosition(280.f, 160.f);

	m_info.setFont(*GlobalFont::get()->getFont());
	m_info.setFillColor(sf::Color(255, 255, 255, 255));
	m_info.setCharacterSize(20);
	m_info.setString("Info");
	m_info.setPosition(280.f, 210.f);

	m_audioPosition.setFont(*GlobalFont::get()->getFont());
	m_audioPosition.setFillColor(sf::Color(255, 255, 255, 255));
	m_audioPosition.setCharacterSize(30);
	m_audioPosition.setString("00:00/00:00");
	m_audioPosition.setPosition(280.f, 250.f);


	for (int i = 0; i < 8; i++)
	{
		m_buttons[i].setFillColor(sf::Color(192, 192, 192, 255));
		m_buttons[i].setSize(sf::Vector2f(60.f, 60.f));
		m_buttons[i].setPosition(20.f + i * 100.f, 380.f);
		m_buttons[i].setOutlineColor(sf::Color(192, 192, 192, 255));
		m_buttons[i].setFillColor(sf::Color(255, 255, 255, 255));

		//m_buttons[i].setOutlineThickness(1.f);

		m_buttons[i].setTexture(&m_transportTexture);
		m_buttons[i].setTextureRect(sf::IntRect(i * 60, 0, 60, 60));

	}


	openFile("/home/promeger/Desktop/test.aif");


}

void Player::processClick(sf::RenderWindow& window)
{
	auto pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

	if (m_playerState == MainScreen)
	{
		if (pos.y > 380 && pos.y < 440)
		{
			int clicked = -1;
			for (int i = 0; i < 8; i++)
			{
				if (pos.x > (20.f + i * 100.f) && pos.x < ((20.f + i * 100.f) + 60))
				{
					clicked = i;
				}
			}


		}
	}
	else if (m_playerState == Browsing)
	{

	}
	else if (m_playerState == Playlist)
	{

	}
}
void Player::draw(sf::RenderWindow& window)
{
	window.draw(m_bg);
	if (m_playerState == MainScreen)
	{
		for (int i = 0; i < 8; i++)
		{
			window.draw(m_buttons[i]);
		}

		window.draw(m_cover);

		window.draw(m_title);
		window.draw(m_artist);
		window.draw(m_album);
		window.draw(m_info);
		window.draw(m_audioPosition);
		m_progress.draw(window);
	}
}

bool Player::openFile(std::string path)
{
	m_currentFilePath = path;
	/*if (!m_musicFile.openFromFile(m_currentFilePath))
	{
		m_currentFilePath = "";
		return false;
	}*/
	

	TagLib::FileRef f(path.c_str());
	
	//Info
	std::wstring sR = std::to_wstring((int)f.audioProperties()->sampleRate());
	std::wstring c = std::to_wstring((int)f.audioProperties()->channels());
	std::wstring b = std::to_wstring((int)f.audioProperties()->bitrate());
	std::wstring ex = std::filesystem::path(path).extension().wstring().erase(0, 1);
	std::transform(ex.begin(), ex.end(), ex.begin(), ::toupper);

	m_info.setString(sf::String(ex + L" " + sR + L"Hz@" + c + L"Ch. B:" + b + L"kbps"));


	if (!f.tag() || f.tag()->isEmpty())
	{
		m_currentArtist = L"";
		m_currentAlbum = L"";

		m_currentTitle = std::filesystem::path(path).filename().wstring();

		m_title.setString(sf::String(m_currentTitle));
		m_album.setString(sf::String(m_currentAlbum));
		m_artist.setString(sf::String(m_currentArtist));

		if (!m_coverTexture.loadFromFile("Media/icons/player/cover.png"))
		{
			// error...
		}

		m_coverTexture.setSmooth(true);
		m_cover.setTexture(m_coverTexture);
		m_cover.setScale(240.f / m_coverTexture.getSize().x, 240.f / m_coverTexture.getSize().y);
		m_cover.setTextureRect(sf::IntRect(0, 0, m_coverTexture.getSize().x, m_coverTexture.getSize().y));

	}
	else
	{

		m_currentArtist = f.tag()->artist().toWString();
		m_currentAlbum = f.tag()->album().toWString();
		m_currentTitle = f.tag()->title().toWString();

		m_title.setString(sf::String(m_currentTitle));
		m_album.setString(sf::String(m_currentAlbum));
		m_artist.setString(sf::String(m_currentArtist));
		auto linS = f.audioProperties()->lengthInSeconds();
		m_audioPosition.setString(sf::String("00:00/" + std::to_string(linS/60) + ":" + std::to_string(linS % 60)));



		TagLib::StringList names = f.complexPropertyKeys();
		for (const auto& name : names)
		{
			const auto& properties = f.complexProperties(name);
			for (const auto& property : properties)
			{
				bool front = false;
				for (const auto& [key, value] : property)
				{
					if (key == "pictureType" && value == "Front Cover")
					{
						front = true;
					}
				}

				if (front)
				{
					for (const auto& [key, value] : property)
					{
						if (value.type() == TagLib::Variant::ByteVector)
						{

							std::ofstream picture;
							picture.open("/tmp/pikczer.png", std::ios_base::out | std::ios_base::binary);
							picture << value.value<TagLib::ByteVector>();
							picture.close();

							if (!m_coverTexture.loadFromFile("/tmp/pikczer.png"))
							{
								// error...
							}

							m_coverTexture.setSmooth(true);
							m_cover.setTexture(m_coverTexture);
							m_cover.setScale(240.f / m_coverTexture.getSize().x, 240.f / m_coverTexture.getSize().y);
							m_cover.setTextureRect(sf::IntRect(0, 0, m_coverTexture.getSize().x, m_coverTexture.getSize().y));

						}
					}

				}
			}
		}
	}


	//Init Len and so on


	
	return true;
}

void Player::play()
{

}

void Player::pause()
{

}

void refreshBrowser()
{

}