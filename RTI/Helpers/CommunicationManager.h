
#pragma once

#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>

class CommunicationManager
{
public:
    static CommunicationManager* get();
    
    void init();
    void shutdown();
    
    void setBrightness(char value);
    void setVolume(char value);
    void toggleAudioOutput();

    char getBrightness();
    char getVolume();
    bool getAudioOutput();

protected:

    CommunicationManager();

    static CommunicationManager* s_instance;

    

    int m_sock;
    int m_len;
    struct sockaddr_un m_remote;

    //Settings
    bool m_audioOutput;
    char m_volume;
    char m_brightness;
};