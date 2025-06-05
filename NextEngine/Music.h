#pragma once
#include <SDL_mixer.h>
#include <string>
#include <iostream>

class Music 
{
private:
    bool isAmbient;
    Mix_Music* music;  // For background music

public:
    Music(const std::string& filePath);
    ~Music();

    void Play(bool isLoop = true);
    void Stop();
    void SetVolume(int volume);  // Volume range: 0 - 128
    bool getAmbient() const;
    void setAmbient(bool ambient);
};
