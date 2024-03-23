#include "Settings.h"
#include "../Helpers/GlobalFont.h"
#include "../Helpers/CommunicationManager.h"

#include <SFML/Graphics.hpp>
#include <iostream>



Settings::Settings() : m_volumeSlider(520, 60, 0, 100, 100, 240, false), m_brightnessSlider(520, 60, 0, 100, 50, 240, false), m_externalAudioTB(710, 105), m_darkmodeTB(710, 105)
{
	m_appTitle = "Settings";
	init();

}

void Settings::init()
{
	const std::string MenuDataTexts[6] =
	{
		"Audio",
		"Display",
		"Information",
		"Debug",
		"Exit to X System",
		"Shutdown"
	};

	const std::string AudioTexts[2] =
	{
		"Volume",
		"External Audio Input (AUX)"
	};

	const std::string DisplayTexts[2] =
	{
		"Brightness",
		"NightMode (INOP)"
	};

	const std::wstring InfoTexts[8][2] =
	{
		{L"Model",L"S80 II"},
		{L"Manufacturer",L"Volvo Cars"},
		{L"Engine",L"Engine Here"},
		{L"VIN",L"VIN HERE"},
		{L"Multimedia Software",L"PrRTI"},
		{L"Software Version",L"0.1 Alpha"},
		{L"Software Codename",L"UNTITLED"},
		{L"Software Compilation Date", L"__DATE__"},
	};

	const std::string MenuDataIcons[6] =
	{
		"Media/menuicons/audio.png",
		"Media/menuicons/display.png",
		"Media/menuicons/info.png",
		"Media/menuicons/dbg.png",
		"Media/menuicons/x.png",
		"Media/menuicons/shutdown.png"
	};

	m_internalState = None;
	m_leftMenuShape.setFillColor(sf::Color(64, 64, 64, 255));
	m_leftMenuShape.setSize(sf::Vector2f(240.f, 440.f));
	m_leftMenuShape.setPosition(0.f, 40.f);

	m_lineDividerMM.setFillColor(sf::Color(192, 192, 192, 255));
	m_lineDividerMM.setSize(sf::Vector2f(240.f, 1.f));
	m_lineDividerMM.setPosition(0.f, 40.f);

	m_lineDividerSM.setFillColor(sf::Color(192, 192, 192, 255));
	m_lineDividerSM.setSize(sf::Vector2f(560.f, 1.f));
	m_lineDividerSM.setPosition(240.f, 40.f);

	m_questionYBtn.setFillColor(sf::Color(64, 64, 64, 255));
	m_questionYBtn.setSize(sf::Vector2f(100.f, 50.f));
	m_questionYBtn.setPosition(350.f, 320.f);

	m_questionNBtn.setFillColor(sf::Color(64, 64, 64, 255));
	m_questionNBtn.setSize(sf::Vector2f(100.f, 50.f));
	m_questionNBtn.setPosition(610.f, 320.f);

	m_questionN.setFont(*GlobalFont::get()->getFont());
	m_questionN.setFillColor(sf::Color(255, 255, 255, 255));
	m_questionN.setString("NO");
	m_questionN.setCharacterSize(25);
	auto qNS = m_questionN.getLocalBounds();
	m_questionN.setPosition(sf::Vector2f(660.f - qNS.width / 2.f, 340.f - qNS.height / 2.f));

	m_questionY.setFont(*GlobalFont::get()->getFont());
	m_questionY.setFillColor(sf::Color(255, 255, 255, 255));
	m_questionY.setString("YES");
	m_questionY.setCharacterSize(25);
	auto qYS = m_questionY.getLocalBounds();
	m_questionY.setPosition(sf::Vector2f(400.f - qYS.width / 2.f, 340.f - qYS.height / 2.f));

	m_question.setFont(*GlobalFont::get()->getFont());
	m_question.setFillColor(sf::Color(255, 255, 255, 255));
	m_question.setCharacterSize(25);

	for (int i = 0; i < 6; i++)
	{
		m_mainMenuItems.push_back(MenuData());
		m_mainMenuItems[i].text.setFont(*GlobalFont::get()->getFont());
		m_mainMenuItems[i].text.setFillColor(sf::Color(255, 255, 255, 255));

		m_mainMenuItems[i].text.setString(MenuDataTexts[i]);
		m_mainMenuItems[i].text.setCharacterSize(25);
		m_mainMenuItems[i].text.setPosition(sf::Vector2f(50.f, 45.f + 45.f * i));

	}

	for (int i = 0; i < 8; i++)
	{
		m_infoScreenA.push_back(sf::Text());
		m_infoScreenB.push_back(sf::Text());
		m_infoScreenA[i].setFont(*GlobalFont::get()->getFont());
		m_infoScreenB[i].setFont(*GlobalFont::get()->getFont());
		m_infoScreenB[i].setFillColor(sf::Color(255, 255, 255, 255));
		m_infoScreenB[i].setFillColor(sf::Color(255, 255, 255, 255));

		m_infoScreenA[i].setString(InfoTexts[i][0]);
		m_infoScreenA[i].setCharacterSize(15);
		m_infoScreenA[i].setPosition(sf::Vector2f(270.f, 50.f + 35.f * i));

		m_infoScreenB[i].setString(InfoTexts[i][1]);
		m_infoScreenB[i].setCharacterSize(15);
		m_infoScreenB[i].setPosition(sf::Vector2f(780.f - m_infoScreenB[i].getLocalBounds().width, 50.f + 35.f * i));
	}

	for (int i = 0; i < 2; i++)
	{
		m_audioTitles.push_back(sf::Text());
		m_audioTitles[i].setFont(*GlobalFont::get()->getFont());
		m_audioTitles[i].setFillColor(sf::Color(255, 255, 255, 255));

		m_audioTitles[i].setString(AudioTexts[i]);
		m_audioTitles[i].setCharacterSize(15);
		m_audioTitles[i].setPosition(sf::Vector2f(270.f, 50.f + 35.f * i));

	}

	for (int i = 0; i < 2; i++)
	{
		m_displayTitles.push_back(sf::Text());
		m_displayTitles[i].setFont(*GlobalFont::get()->getFont());
		m_displayTitles[i].setFillColor(sf::Color(255, 255, 255, 255));

		m_displayTitles[i].setString(DisplayTexts[i]);
		m_displayTitles[i].setCharacterSize(15);
		m_displayTitles[i].setPosition(sf::Vector2f(270.f, 50.f + 35.f * i));

	}
}
void Settings::processClick(sf::RenderWindow& window)
{
	auto pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

	for (int i = 0; i < 6; i++)
	{
		if (pos.x > 0.f && pos.x < 240.f)
		{
			//Proces left menu
			if (pos.y > 40.f + i * 45.f && pos.y < 40.f + (i + 1) * 45.f)
				m_internalState = (Settings::SettingsState)i;

		}
	}

	if (m_internalState == Settings::ShutDown)
	{
		if (m_questionN.getGlobalBounds().contains(pos))
			m_internalState = Settings::None;

		if (m_questionY.getGlobalBounds().contains(pos))
		{
			CommunicationManager::get()->shutdown();
			exit(0);
		}
	}
	else if (m_internalState == Settings::ExitToX)
	{
		if (m_questionN.getGlobalBounds().contains(pos))
			m_internalState = Settings::None;

		if (m_questionY.getGlobalBounds().contains(pos))
		{
			system("startlxde");
			exit(0);
		}

	}
	else if (m_internalState == Settings::Audio)
	{
		auto oldV = m_volumeSlider.getValue();
		m_volumeSlider.processClick(window);
		auto newV = m_volumeSlider.getValue();

		if (oldV != newV)
			CommunicationManager::get()->setVolume((char)newV);

		auto oldOV = m_externalAudioTB.getValue();
		m_externalAudioTB.processClick(window);
		auto newOV = m_externalAudioTB.getValue();

		if (oldOV != newOV)
			CommunicationManager::get()->toggleAudioOutput();
	}
	else if (m_internalState == Settings::Display)
	{
		auto oldV = m_brightnessSlider.getValue();
		m_brightnessSlider.processClick(window);
		auto newV = m_brightnessSlider.getValue();

		if (oldV != newV)
			CommunicationManager::get()->setBrightness((char)newV);

		m_darkmodeTB.processClick(window);
	}

}

void Settings::draw(sf::RenderWindow& window)
{
	window.clear(sf::Color(32, 32, 32, 255));
	
	window.draw(m_leftMenuShape);
	renderMenuElements(window);
	renderSubMenuElements(window);
}

void Settings::renderMenuElements(sf::RenderWindow& window)
{
	for(int i = 0; i < 6; i++)
	{
		if (m_mainMenuItems[i].icon)
			window.draw(*m_mainMenuItems[i].icon);

		window.draw(m_mainMenuItems[i].text);
		m_lineDividerMM.setPosition(0.f, m_mainMenuItems[i].text.getPosition().y + 40.f);
		window.draw(m_lineDividerMM);
	}
}

void Settings::renderSubMenuElements(sf::RenderWindow& window)
{

	switch (m_internalState)
	{
	case Settings::None:
		break;
	case Settings::Audio:
		for (int i = 0; i < 2; i++)
		{
			window.draw(m_audioTitles[i]);
			m_lineDividerSM.setPosition(240.f, m_audioTitles[i].getPosition().y + 30.f);
			window.draw(m_lineDividerSM);
		}
		m_volumeSlider.draw(window);
		m_externalAudioTB.draw(window);

		break;
	case Settings::Display:
		for (int i = 0; i < 2; i++)
		{
			window.draw(m_displayTitles[i]);
			m_lineDividerSM.setPosition(240.f, m_displayTitles[i].getPosition().y + 30.f);
			window.draw(m_lineDividerSM);
		}
		m_brightnessSlider.draw(window);
		m_darkmodeTB.draw(window);
		break;
	case Settings::Information:
		for (int i = 0; i < 8; i++)
		{
			window.draw(m_infoScreenA[i]);
			window.draw(m_infoScreenB[i]);
			m_lineDividerSM.setPosition(240.f, m_infoScreenA[i].getPosition().y + 30.f);
			window.draw(m_lineDividerSM);
		}
		break;
	case Settings::Debug:
		break;
	case Settings::ExitToX:
	{
		m_question.setString("Are you sure to exit to X system?");
		auto q = m_question.getLocalBounds();
		m_question.setPosition(sf::Vector2f(520.f - q.width / 2.f, 180.f - q.height / 2.f));
		window.draw(m_question);
		window.draw(m_questionYBtn);
		window.draw(m_questionY);
		window.draw(m_questionNBtn);
		window.draw(m_questionN);
		break;
	}
	case Settings::ShutDown:
	{
		m_question.setString("Are you sure to shut down the system?");
		auto q = m_question.getLocalBounds();
		m_question.setPosition(sf::Vector2f(520.f - q.width / 2.f, 180.f - q.height / 2.f));
		window.draw(m_question);
		window.draw(m_questionYBtn);
		window.draw(m_questionY);
		window.draw(m_questionNBtn);
		window.draw(m_questionN);
		break;
	}
	default:
		break;
	}
}