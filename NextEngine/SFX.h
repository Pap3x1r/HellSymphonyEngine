#pragma once

#include <SDL_mixer.h>
#include <string>
#include <iostream>

class SFX 
{
private:
    bool isAmbient = false;
    Mix_Chunk* chunk;  // For sound effects

public:

    SFX(const std::string& filePath);
    ~SFX();

    void Play(bool isLoop = false);
    void Stop();
    void SetVolume(int volume);  // Volume range: 0 - 128
    bool getAmbient() const;
    void setAmbient(bool ambient);
};
