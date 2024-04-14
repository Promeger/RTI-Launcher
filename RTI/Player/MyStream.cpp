#include "MyStream.h"

#include <iostream>

bool MyStream::open(const std::string& location)
{
    std::string sR = location.substr(0, location.find(':'));
    std::string ch = location.substr(location.find(':') + 1);
    m_sampleRate = stoi(sR);
    m_channels = stoi(ch);
    initialize(m_channels, m_sampleRate);

    return true;
}

void MyStream::bindData(std::vector<short> fileData)
{
    m_fileData = fileData;
    m_maxSample = fileData.size();
    m_currSample = 0;
}

bool MyStream::onGetData(Chunk& data)
{
    if (m_currSample >= m_maxSample)
        return false;

    std::size_t amount = m_sampleRate * m_channels * 5;
    if (m_currSample + amount > m_maxSample)
    {
        amount = m_maxSample - m_currSample;
    }

    data.sampleCount = amount;
    data.samples = &m_fileData[m_currSample];

    m_currSample += amount;
    
    return true;
}

void MyStream::onSeek(sf::Time timeOffset)
{
    m_currSample = (timeOffset.asSeconds() * m_sampleRate * m_channels);

}