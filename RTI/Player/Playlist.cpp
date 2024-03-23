#include "Playlist.h"

#include <fstream>
#include <codecvt>
#include <locale>
#include <taglib/fileref.h>
#include <taglib/tag.h>

template<typename C>
auto split(C&& str, const std::wstring& delimiter)
{
	std::vector<typename std::remove_reference<C>::type> strings;

	for (auto p = str.data(), end = p + str.length();
		p != end;
		p += ((p == end) ? 0 : delimiter.length()))
	{
		const auto pre = p;
		p = std::search(pre, end, delimiter.cbegin(), delimiter.cend());

		if (p != pre)
		{
			strings.emplace_back(pre, p - pre);
		}
	}

	return strings;
}

template <typename t> void movee(std::vector<t>& v, size_t oldIndex, size_t newIndex)
{
	if (oldIndex > newIndex)
		std::rotate(v.rend() - oldIndex - 1, v.rend() - oldIndex, v.rend() - newIndex);
	else
		std::rotate(v.begin() + oldIndex, v.begin() + oldIndex + 1, v.begin() + newIndex + 1);
}

Playlist::Playlist() : m_currentIdx(0), m_maxSong(0), m_player(NULL)
{

}

void Playlist::saveToFile(std::string path)
{
	std::wofstream myfile(path, std::ios::binary);
	std::locale loc(std::locale::classic(), new std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>);
	myfile.imbue(loc);
	myfile << wchar_t(0xFEFF) /* UCS2-LE BOM */;



	for (auto& e : m_playlist)
	{
		myfile << std::wstring(e.path.begin(), e.path.end()) << "|0x01|" << e.title << "|0x01|" << e.artist << "\n";
	}

		
	myfile.close();
}

void Playlist::openFromFile(std::string path)
{
	std::wifstream myfile(path, std::ios::binary);
	std::locale loc(std::locale::classic(), new std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>);
	if (myfile.is_open())
	{
		// apply BOM-sensitive UTF-16 facet
		myfile.imbue(std::locale(myfile.getloc(), new std::codecvt_utf16<wchar_t, 0x10ffff, std::consume_header>));

		std::wstring wline;
		while (std::getline(myfile, wline))
		{
			//Parse
			const auto strings = split(wline, L"|0x01|");
				PlayListEntry e;

				e.path = std::string(strings.at(0).begin(), strings.at(0).end());
				e.title = strings.at(1);
				e.artist = strings.at(2);
				m_playlist.push_back(e);
		}

	}

		myfile.close();
}


void Playlist::addToPlaylist(std::string path)
{
	PlayListEntry entry;
	entry.path = path;

	//Load Tag
	TagLib::FileRef f(path.c_str());
	if (!f.tag() || f.tag()->isEmpty())
	{
		entry.artist = L"";
		entry.title = std::wstring(path.begin(), path.end());
	}
	else
	{
		entry.artist = f.tag()->artist().toWString();
		entry.title = f.tag()->title().toWString();
	}

	m_playlist.push_back(entry);
	m_maxSong += 1;
}

void Playlist::removeFromPlaylist(unsigned int idx)
{
	m_maxSong -= 1;
	m_playlist.erase(m_playlist.begin() + idx);
}

void Playlist::move(unsigned int idx, unsigned int newPos)
{
	movee(m_playlist, idx, newPos);
}

void Playlist::play(unsigned int idx)
{
	m_currentIdx = idx;
	m_player->openFile(m_playlist.at(m_currentIdx).path);
}

void Playlist::bindPlayer(Player* p)
{
	m_player = p;
}