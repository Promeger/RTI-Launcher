#include <SFML/Audio.hpp>

class MyStream : public sf::SoundStream
{
public:

    bool open(const std::string& location);
    void bindData(std::vector<short> fileData);

private:

    virtual bool onGetData(Chunk& data);
    
    virtual void onSeek(sf::Time timeOffset);

    std::vector<short> m_fileData;
    unsigned long long m_maxSample;
    unsigned long long m_currSample;
    int m_sampleRate;
    int m_channels;
};