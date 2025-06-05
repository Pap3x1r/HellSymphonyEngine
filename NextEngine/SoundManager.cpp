#include "SoundManager.h"
#include <iostream>
#include <fstream>

#define KK_ERROR(msg, ...) \
    do { \
        std::cerr << "[ERROR] " << msg << std::endl; \
    } while(0)



SoundManager* SoundManager::instance = nullptr;

SoundManager::SoundManager() 
{
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    loadVolumeFromFile();

    int flags = Mix_Init(MIX_INIT_MP3);
    if ((flags & MIX_INIT_MP3) == 0) {
        std::cerr << "MP3 support not available: " << Mix_GetError() << std::endl;
    }
}

SoundManager::~SoundManager() {
    Cleanup();
}
SoundManager* SoundManager::GetInstance()
{
    if (instance == nullptr) {
        instance = new SoundManager();
    }
    return instance;
}
void SoundManager::LoadSFX(const std::string& name, const std::string& filePath, bool ambient)
{   
    if (SFXSounds.find(name) == SFXSounds.end()) {
        SFXSounds[name] = new SFX(filePath);
    }
    else {
        KK_ERROR("SFX {0} already loaded!", name);
    }
}
void SoundManager::LoadMusic(const std::string& name, const std::string& filePath, bool ambient)
{
    if (musicSounds.find(name) == musicSounds.end()) {
        musicSounds[name] = new Music(filePath);
    }
    else {
        KK_ERROR("Music {0} already loaded!", name);
    }
}

void SoundManager::PlaySFX(const std::string& name, bool isloop)
{
    if (SFXSounds.find(name) != SFXSounds.end()) {
        SFXSounds[name]->Play(isloop);
    }
    else {
        KK_ERROR("SFX {0} not found!", name);
    }
}
void SoundManager::PlayMusic(const std::string& name, bool isloop)
{
    if (musicSounds.find(name) != musicSounds.end()) {
        musicSounds[name]->Play(isloop);
    }
    else {
        KK_ERROR("Music {0} not found!", name);
    }
}


void SoundManager::StopSFX(const std::string& name)
{
    if (SFXSounds.find(name) != SFXSounds.end()) {
        SFXSounds[name]->Stop();
    }
    else
    {
        KK_ERROR("Can't stop SFX. No SFX in list : {0}", name);
    }
}
void SoundManager::StopMusic(const std::string& name)
{
    if (musicSounds.find(name) != musicSounds.end()) {
        musicSounds[name]->Stop();
    }
    else
    {
        KK_ERROR("Can't stop music. No music in list : {0}", name);
    }
}

void SoundManager::SetVolumeSFX(const std::string& name, int volume)
{
    if (SFXSounds.find(name) != SFXSounds.end()) {

        int vol = toSDLVolume(currentSoundEffectVolume * currentMasterVolume);
        if (SFXSounds[name]->getAmbient()) {
            vol = toSDLVolume(currentAmbientVolume * currentMasterVolume);
        }
        
        SFXSounds[name]->SetVolume(vol);
    }
    else
    {
        KK_ERROR("Can't set SFX Volume. No music in list : {0}", name);
    }
}
void SoundManager::SetVolumeMusic(const std::string& name, int volume)
{
    if (musicSounds.find(name) != musicSounds.end()) {
        int vol = toSDLVolume(currentMusicVolume * currentMasterVolume);
        if (SFXSounds[name]->getAmbient()) {
            vol = toSDLVolume(currentAmbientVolume * currentMasterVolume);
        }
        musicSounds[name]->SetVolume(vol);
    }
    else
    {
        KK_ERROR("Can't set music Volume. No music in list : {0}", name);
    }
}

void SoundManager::SetVolumeAllSFX(int volume)
{
    for (auto music : SFXSounds)
    {
        SetVolumeSFX(music.first, volume);
    }
}
void SoundManager::SetVolumeAllMusic(int volume)
{
    for (auto music : musicSounds)
    {
        SetVolumeMusic(music.first, volume);
    }
}

void SoundManager::updateVolumeSFX(const std::string& name)
{
    if (SFXSounds.find(name) != SFXSounds.end()) {
        int vol = toSDLVolume(currentSoundEffectVolume * currentMasterVolume);
        if (SFXSounds[name] != nullptr) {
            if (SFXSounds[name]->getAmbient()) {
                vol = toSDLVolume(currentAmbientVolume * currentMasterVolume);
            }
        }
        else {

        }
        SFXSounds[name]->SetVolume(vol);
    }
    else
    {
        KK_ERROR("Can't set SFX Volume. No music in list : {0}", name);
    }
}

void SoundManager::updateVolumeMusic(const std::string& name)
{
    if (musicSounds.find(name) != musicSounds.end()) {
        int vol = toSDLVolume(currentMusicVolume * currentMasterVolume);
        if (musicSounds[name] != nullptr) {
            if (musicSounds[name]->getAmbient()) {
                vol = toSDLVolume(currentAmbientVolume * currentMasterVolume);
            }
        }
        else {

        }
        musicSounds[name]->SetVolume(vol);
    }
    else
    {
        KK_ERROR("Can't set music Volume. No music in list : {0}", name);
    }
}

void SoundManager::updateVolumeAllSFX()
{
    for (auto music : SFXSounds)
    {
        updateVolumeSFX(music.first);
    }
}
void SoundManager::updateVolumeAllMusic()
{
    for (auto music : musicSounds)
    {
        updateVolumeMusic(music.first);
    }
}

void SoundManager::Cleanup()
{
    for (auto& pair : SFXSounds) {
        delete pair.second;
    }
    SFXSounds.clear();

    for (auto& pair : musicSounds) {
        delete pair.second;
    }
    musicSounds.clear();
}

void SoundManager::setMasterVolume(float volume) {
    currentMasterVolume = volume;
}

void SoundManager::setMusicVolume(float volume) {
    currentMusicVolume = volume;
}

void SoundManager::setSoundEffectVolume(float volume) {
    currentSoundEffectVolume = volume;
}

void SoundManager::setAmbientVolume(float volume) {
    currentAmbientVolume = volume;
}

float SoundManager::getMasterVolume() const {
    return currentMasterVolume;
}

float SoundManager::getMusicVolume() const {
    return currentMusicVolume;
}

float SoundManager::getSoundEffectVolume() const {
    return currentSoundEffectVolume;
}

float SoundManager::getAmbientVolume() const {
    return currentAmbientVolume;
}

void SoundManager::update() {
    updateVolumeAllSFX();
    updateVolumeAllMusic();
}

void SoundManager::StopAllSounds()
{
    // Stop all sound effects
    for (auto& pair : SFXSounds) {
        if (pair.second != nullptr) {
            pair.second->Stop();
        }
    }

    // Stop all music
    for (auto& pair : musicSounds) {
        if (pair.second != nullptr) {
            pair.second->Stop();
        }
    }
}

void SoundManager::saveVolumeToFile() {
    std::ofstream volumeFile("../Resource/Audio/volumeFile.txt");
    
    if (volumeFile.is_open()) {
    	volumeFile << currentMasterVolume << "\n" << currentSoundEffectVolume << "\n" << currentMusicVolume << "\n" << currentAmbientVolume << "\n";
    	volumeFile.close();
    	std::cout << "Volume settings saved to ../Resource/Audio/volumeFile.txt" << std::endl;
    }
    else {
    	std::cerr << "Error: Could not save volume to file: ../Resource/Audio/volumeFile.txt" << std::endl;
    }
}

void SoundManager::loadVolumeFromFile() {
    std::ifstream volumeFile("../Resource/Audio/volumeFile.txt");

    if (volumeFile.is_open()) {
        float master = 1.0f, sfx = 1.0f, music = 1.0f, ambient = 1.0f;

        volumeFile >> master >> sfx >> music >> ambient;

        // Clamp values between 0.0 and 1.0 if needed (optional safety)
        currentMasterVolume = std::clamp(master, 0.0f, 1.0f);
        currentSoundEffectVolume = std::clamp(sfx, 0.0f, 1.0f);
        currentMusicVolume = std::clamp(music, 0.0f, 1.0f);
        currentAmbientVolume = std::clamp(ambient, 0.0f, 1.0f);

        volumeFile.close();
        update();  // Refresh all volumes based on loaded values

        std::cout << "Volume settings loaded from ../Resource/Audio/volumeFile.txt" << std::endl;
    }
    else {
        std::cerr << "Error: Could not open volume file for reading: ../Resource/Audio/volumeFile.txt" << std::endl;
    }
}

