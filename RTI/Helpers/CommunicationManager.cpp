#include "CommunicationManager.h"

#include <iostream>

CommunicationManager* CommunicationManager::s_instance = NULL;

CommunicationManager::CommunicationManager()
{
	init();
}

CommunicationManager* CommunicationManager::get()
{
	if (!s_instance)
		s_instance = new CommunicationManager();

	return s_instance;
}

void CommunicationManager::init()
{
	m_sock = socket(AF_UNIX, SOCK_STREAM, 0);
	m_remote.sun_family = AF_UNIX;
	strcpy(m_remote.sun_path, "/tmp/volveCommSock");
	m_len = sizeof(m_remote);

	if (connect(m_sock, (sockaddr*)&m_remote, m_len) == -1)
		return;

	m_volume = 100;
	m_brightness = 50;
	m_audioOutput = true;
}

void CommunicationManager::shutdown()
{
	std::string args = "SHUTDOWN";
	if (write(m_sock, args.c_str(), sizeof(args.c_str())) == -1) {
		std::cerr << "Error Sending" << std::endl;
		return;
	}

}

void CommunicationManager::setBrightness(char value)
{
	m_brightness = (value > 100 ? 100 : (value < 0 ? 0 : value));

	std::string args = "BRIGHTNESS " + std::to_string(m_brightness);
	if (write(m_sock, args.c_str(), sizeof(args.c_str())) == -1) {
		std::cerr << "Error Sending" << std::endl;
		return;
	}

}

void CommunicationManager::setVolume(char value)
{
	m_volume = (value > 100 ? 100 : (value < 0 ? 0 : value));

	std::string args = "VOLUME " + std::to_string(m_volume);
	if (write(m_sock, args.c_str(), sizeof(args.c_str())) == -1) {
		std::cerr << "Error Sending" << std::endl;
		return;
	}

}

void CommunicationManager::toggleAudioOutput()
{
	m_audioOutput = !m_audioOutput;
	std::string args = "OUTPUT " + std::to_string((m_audioOutput ? 1 : 0));
	if (write(m_sock, args.c_str(), sizeof(args.c_str())) == -1) {
		std::cerr << "Error Sending" << std::endl;
		return;
	}

}

char CommunicationManager::getBrightness()
{
	return m_brightness;
}

char CommunicationManager::getVolume()
{
	return m_volume;
}

bool CommunicationManager::getAudioOutput()
{
	return m_audioOutput;
}