#include "Music.h"

Music::Music(const std::string& filePath) : music(nullptr) 
{
    music = Mix_LoadMUS(filePath.c_str());

    if (!music) {
        std::cerr << "Failed to load music: {0}" << Mix_GetError() << std::endl;
    }
}

Music::~Music() 
{
    Mix_FreeMusic(music);
}

void Music::Play(bool isLoop)
{
    if (isLoop) {
        Mix_PlayMusic(music, -1);
    }
    else {
        Mix_PlayMusic(music, 0);
    }
}

void Music::Stop() 
{
    Mix_HaltMusic();
}

void Music::SetVolume(int volume) 
{
    Mix_VolumeMusic(volume);
}

bool Music::getAmbient() const {
    return isAmbient;
}

void Music::setAmbient(bool ambient) {
    isAmbient = ambient;
}

