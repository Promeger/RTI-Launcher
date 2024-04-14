#include "Player.h"

#include "../Helpers/GlobalFont.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <locale>

#include <taglib/fileref.h>
#include <taglib/tag.h>

#include <sndfile.hh>

int printError(const char* prefix, int errorCode) {
	if (errorCode == 0) {
		return 0;
	}
	else {
		const size_t bufsize = 64;
		char buf[bufsize];

		
		fprintf(stderr, "%s (%d: %s)\n", prefix, errorCode, buf);

		return errorCode;
	}
}

namespace fs = std::filesystem;

const std::vector<std::string> Player::s_brExtensions = std::vector<std::string>{ ".mp3", ".wav", ".aiff", ".aif", ".m4a", ".aac", ".flac", ".alac"};

Player::Player() : m_progress(40, 340, 0, 100, 100, 720, false), m_playerState(MainScreen), m_playState(Paused), m_currentFilePath(""), m_brIndex(0), m_brCurrentPath("/"), m_audioFileLen(0)
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


	if (!m_brFileTexture.loadFromFile("Media/icons/player/file.png"))
	{
		// error...
	}

	if (!m_brFolderTexture.loadFromFile("Media/icons/player/folder.png"))
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

	m_browserDivider.setFillColor(sf::Color(192, 192, 192, 255));
	m_browserDivider.setSize(sf::Vector2f(800.f, 1.f));
	m_browserDivider.setPosition(0.f, 40.f);


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

	std::string Tmpbtns[4] = { "Bck", "LUp", "Up", "Dn" };
	for (int i = 0; i < 4; i++)
	{
		m_brButtons[i].setFillColor(sf::Color(192, 192, 192, 255));
		m_brButtons[i].setSize(sf::Vector2f(50.f, 50.f));
		m_brButtons[i].setPosition(200.f + i * 100.f, 420.f);
		m_brButtons[i].setOutlineColor(sf::Color(192, 192, 192, 255));

		m_brButtonsTexts[i].setFont(*GlobalFont::get()->getFont());
		m_brButtonsTexts[i].setFillColor(sf::Color(0, 0, 0, 255));
		m_brButtonsTexts[i].setCharacterSize(20);
		m_brButtonsTexts[i].setString(Tmpbtns[i]);
		m_brButtonsTexts[i].setPosition(210.f + i * 100.f, 430.f);


	}


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

			switch (clicked)
			{
			case 0:
				refreshBrowser();
				m_playerState = Browsing;
				break;
			case 1:
				m_playerState = Playlist;
				break;
			case 2:
				prev();
				break;
			case 3:
				rewind();
				break;
			case 4:
				play();
				break;
			case 5:
				pause();
				break;
			case 6:
				ff();
				break;
			case 7:
				next();
				break;
			default:
				break;
			}

		}

		if (m_progress.processClick(window))
		{
			auto val = m_progress.getValue();

			m_musicFile.setPlayingOffset(sf::seconds(m_audioFileLen * val / 100.f));
		}
	}
	else if (m_playerState == Browsing)
	{
		if (pos.y >= 40 && pos.y < 390)
		{
			int index = (pos.y - 40) / 35;

			if (index < m_brCurrentEntries.size())
			{
				if (m_brCurrentEntries.at(index).browserData.first == 0)
				{
					m_brCurrentPath = m_brCurrentEntries.at(index).browserData.second.second;
					refreshBrowser();
				}
				else
				{
					if (pos.x > 754.f && pos.x < 770.f)
					{
						//Add To plist - Todo with plist impl
					}
					else
					{

						m_playerState = MainScreen;

						if (m_musicFile.getStatus() != sf::SoundSource::Stopped)
							m_musicFile.stop();

						openFile(m_brCurrentEntries.at(index).browserData.second.second);

					}
				}

			}
		}
		}
		if (pos.y >= 420 && pos.y < 470.f)
		{
			
			for (int i = 0; i < 4; i++)
			{
				if (pos.x > 200.f + (i * 100.f) && pos.x < (200.f + (i * 100.f) + 50.f))
				{
					if (i == 0)
					{
						m_playerState = MainScreen;
					}
					else if (i == 1)
					{
						if (m_brCurrentPath.length() < 2)
							break;
						
						m_brCurrentPath = m_brCurrentPath.substr(0, m_brCurrentPath.find_last_of('/'));
						refreshBrowser();
					}
					else if (i == 2)
					{
						m_brIndex = (m_brIndex == m_brMaxIndex) ? m_brMaxIndex : m_brIndex + 1;
						invalidateBrowser();
					}
					else
					{
						m_brIndex = (m_brIndex == 0) ? 0 : m_brIndex - 1;
						invalidateBrowser();


					}
				}
			}
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
		int currLen = int(m_musicFile.getPlayingOffset().asSeconds());
		std::string m1 = currLen % 60 < 10 ? "0" : "";
		std::string m2 = m_audioFileLen % 60 < 10 ? "0" : "";
		m_audioPosition.setString(sf::String(std::to_string(currLen / 60) + ":" + m1 + std::to_string(currLen % 60) + "/" + std::to_string(m_audioFileLen / 60) + ":" + m2 + std::to_string(m_audioFileLen % 60)));

		if(m_audioFileLen > 0.f)
			m_progress.setPercentValue(100 * currLen / m_audioFileLen);

		if (currLen >= m_audioFileLen)
			next();
		
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
	else if (m_playerState == Browsing)
	{
		for (int i = 0; i < m_brCurrentEntries.size(); i++)
		{
			//Render Text and buttons
			window.draw(*m_brCurrentEntries[i].icon);
			window.draw(m_brCurrentEntries[i].text);
			window.draw(m_brCurrentEntries[i].addToPlist);
			window.draw(m_brCurrentEntries[i].addToPlistText);
			m_browserDivider.setPosition(0.f, m_brCurrentEntries[i].text.getPosition().y + 30.f);
			window.draw(m_browserDivider);
		}


		for (int i = 0; i < 4; i++)
		{
			//Render Text and buttons
			window.draw(m_brButtons[i]);
			window.draw(m_brButtonsTexts[i]);
		}

	}
	else if (m_playerState == Playlist)
	{
		 
	}
}

bool Player::openFile(std::string path)
{
	m_currentFilePath = path;
	

	TagLib::FileRef f(path.c_str());
	
	//Info
	std::wstring sR = std::to_wstring((int)f.audioProperties()->sampleRate());
	std::wstring c = std::to_wstring((int)f.audioProperties()->channels());
	std::wstring b = std::to_wstring((int)f.audioProperties()->bitrate());
	std::wstring ex = fs::path(path).extension().wstring().erase(0, 1);
	std::transform(ex.begin(), ex.end(), ex.begin(), ::toupper);

	m_info.setString(sf::String(ex + L" " + sR + L"Hz@" + c + L"Ch. B:" + b + L"kbps"));


	if (!f.tag() || f.tag()->isEmpty())
	{
		m_currentArtist = L"";
		m_currentAlbum = L"";

		m_currentTitle = fs::path(path).filename().wstring();

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
		m_audioFileLen = f.audioProperties()->lengthInSeconds();
		m_audioPosition.setString(sf::String("00:00/" + std::to_string(m_audioFileLen /60) + ":" + std::to_string(m_audioFileLen % 60)));



		TagLib::StringList names = f.complexPropertyKeys();
		bool front = false;

		for (const auto& name : names)
		{
			const auto& properties = f.complexProperties(name);
			for (const auto& property : properties)
			{
				for (const auto& [key, value] : property)
				{
					if (key == "pictureType" && value == "Front Cover")
					{
						for (const auto& [key, value] : property)
						{
							if (value.type() == TagLib::Variant::ByteVector)
							{
								front = true;
								auto a = value.value<TagLib::ByteVector>();
								if (!m_coverTexture.loadFromMemory(a.data(), a.size()))
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

		if (!front)
		{
			if (!m_coverTexture.loadFromFile("Media/icons/player/cover.png"))
			{
				// error...
			}

			m_coverTexture.setSmooth(true);
			m_cover.setTexture(m_coverTexture);
			m_cover.setScale(240.f / m_coverTexture.getSize().x, 240.f / m_coverTexture.getSize().y);
			m_cover.setTextureRect(sf::IntRect(0, 0, m_coverTexture.getSize().x, m_coverTexture.getSize().y));

		}
	}



	//LoadFile
	SndfileHandle myf = SndfileHandle( path);
	m_currentSongData.resize(myf.frames() * myf.channels());
	myf.read(&m_currentSongData[0], int(myf.frames() * myf.channels()) );

	std::string qualifier = std::to_string(myf.samplerate()) + ":" + std::to_string(myf.channels());
	m_musicFile.bindData(m_currentSongData);
	m_musicFile.open(qualifier);



	m_musicFile.play();


	
	return true;
}

void Player::play()
{
	if(m_musicFile.getStatus() != sf::SoundSource::Playing)
		m_musicFile.play();
}

void Player::pause()
{
	if (m_musicFile.getStatus() != sf::SoundSource::Paused)
		m_musicFile.pause();
}

void Player::ff()
{
	auto offset = m_musicFile.getPlayingOffset().asSeconds();
	offset += 2.f;

	if (offset >= float(m_audioFileLen))
		next();
	else
		m_musicFile.setPlayingOffset(sf::seconds(offset));
}

void Player::rewind()
{
	auto offset = m_musicFile.getPlayingOffset().asSeconds();
	offset -= 2.f;

	if (offset <= 0.f)
		offset = 0.f;

	m_musicFile.setPlayingOffset(sf::seconds(offset));
}

void Player::next()
{
	if (m_musicFile.getStatus() != sf::SoundSource::Stopped)
		m_musicFile.stop();

	//Todo in plist
}

void Player::prev()
{
	if (m_musicFile.getStatus() != sf::SoundSource::Stopped)
		m_musicFile.stop();

	//Todo in plist
}

void Player::refreshBrowser()
{
	try
	{
		m_brData.clear();
		std::locale loc;

		if (fs::is_empty(m_brCurrentPath))
			return;

		for (auto& p : fs::directory_iterator(m_brCurrentPath))
			if (p.is_directory())
			{
				m_brData.push_back(std::make_pair(0, std::make_pair(p.path().filename().wstring(), p.path().string())));
			}
			else
			{
				auto ex = p.path().extension().string();
				std::transform(ex.begin(), ex.end(), ex.begin(), ::tolower);
				if (std::find(Player::s_brExtensions.begin(), Player::s_brExtensions.end(), ex) != Player::s_brExtensions.end())
				{
					m_brData.push_back(std::make_pair(1, std::make_pair(p.path().filename().wstring(), p.path().string())));
				}
			}

		std::sort(m_brData.begin(), m_brData.end(), [](auto& left, auto& right) {
			
			if (left.first != right.first) {
				return left.first < right.first;
			}

			return left.second.first < right.second.first;
				
			});

	

		m_brMaxIndex = m_brData.size() / 10;
		m_brIndex = 0;

		invalidateBrowser();
	}
	catch (...)
	{
		std::cout << "Access denied" << std::endl;
	}

}

void Player::invalidateBrowser()
{
	auto start = m_brData.begin() + m_brIndex * 10;
	auto end = (m_brIndex < m_brMaxIndex) ? start + 10 : m_brData.end();
	int helper = 0;

	m_brCurrentEntries.clear();

	for (auto i = start; i != end; i++)
	{
		m_brCurrentEntries.push_back(BrowserEntry());
		m_brCurrentEntries.back().text.setFont(*GlobalFont::get()->getFont());
		m_brCurrentEntries.back().text.setFillColor(sf::Color(255, 255, 255, 255));
		m_brCurrentEntries.back().addToPlistText.setFont(*GlobalFont::get()->getFont());
		m_brCurrentEntries.back().addToPlistText.setFillColor(sf::Color(255, 255, 255, 255));

		m_brCurrentEntries.back().text.setString(i->second.first);
		m_brCurrentEntries.back().text.setCharacterSize(15);
		m_brCurrentEntries.back().text.setPosition(sf::Vector2f(60.f, 50.f + 35.f * helper));

		m_brCurrentEntries.back().icon = new sf::Sprite();
		m_brCurrentEntries.back().icon->setTexture(i->first ? m_brFileTexture : m_brFolderTexture);
		m_brCurrentEntries.back().icon->setPosition(sf::Vector2f(20.f, 50.f + 35.f * helper));
		m_brCurrentEntries.back().browserData = *i;

		if (i->first)
		{
			m_brCurrentEntries.back().addToPlist.setSize(sf::Vector2f(25.f, 25.f));
			m_brCurrentEntries.back().addToPlist.setPosition(sf::Vector2f(745.f, 50.f + 35.f * helper));
			m_brCurrentEntries.back().addToPlist.setFillColor(sf::Color(128, 128, 128));

			m_brCurrentEntries.back().addToPlistText.setString("+");
			m_brCurrentEntries.back().addToPlistText.setCharacterSize(35);
			m_brCurrentEntries.back().addToPlistText.setPosition(sf::Vector2f(748.f, 50.f + (35.f * helper) - 10.f));

		}

		

		helper++;
	}
	



}