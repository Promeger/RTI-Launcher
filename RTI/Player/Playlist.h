#pragma once

#include "Player.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Playlist
{
public:
	struct PlayListEntry
	{
		std::string path;
		std::wstring artist;
		std::wstring title;
	};

	Playlist();

	void saveToFile(std::string path);
	void openFromFile(std::string path);

	void addToPlaylist(std::string path);
	void removeFromPlaylist(unsigned int idx);
	void move(unsigned int idx, unsigned int newPos);

	void play(unsigned int idx);
	
	void bindPlayer(Player* p);

private:
	unsigned int m_currentIdx;
	unsigned int m_maxSong;
	Player* m_player;
	std::vector<PlayListEntry> m_playlist;
};