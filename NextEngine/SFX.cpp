#include "SFX.h"

SFX::SFX(const std::string& filePath) : chunk(nullptr) 
{
    chunk = Mix_LoadWAV(filePath.c_str());

    if (!chunk) {
        std::cerr << "Failed to load sound effect: {0}" << Mix_GetError() << std::endl;
    }
}

SFX::~SFX() 
{
    Mix_FreeChunk(chunk);
}

void SFX::Play(bool isLoop) 
{
    Mix_PlayChannel(-1, chunk, isLoop);
}

void SFX::Stop() 
{
    Mix_HaltChannel(-1);
}

void SFX::SetVolume(int volume) 
{
    Mix_VolumeChunk(chunk, volume);
}

bool SFX::getAmbient() const {
    return isAmbient;
}

void SFX::setAmbient(bool ambient) {
    isAmbient = ambient;
}