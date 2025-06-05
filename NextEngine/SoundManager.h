#pragma once
#include <map>
#include <string>
#include "Music.h"
#include "SFX.h"
#include <algorithm>

inline int lerp(int a, int b, float t) {
    t = std::clamp(t, 0.0f, 1.0f);  // ensures it's between 0 and 1
    return static_cast<int>(a + (b - a) * t);
}

class SoundManager {
private:

    static SoundManager* instance;
    std::map<std::string, Music*> musicSounds;
    std::map<std::string, SFX*> SFXSounds;

    float currentMasterVolume = 1.0f;
    float currentSoundEffectVolume = 1.0f;
    float currentMusicVolume = 1.0f;
    float currentAmbientVolume = 1.0f;

public:
    SoundManager();
    ~SoundManager();

    static SoundManager* GetInstance();

    void LoadSFX(const std::string& name, const std::string& filePath, bool ambient);
    void LoadMusic(const std::string& name, const std::string& filePath, bool ambient);

    void PlaySFX(const std::string& name, bool isloop = 0);
    void PlayMusic(const std::string& name, bool isloop = 1);

    void StopSFX(const std::string& name);
    void StopMusic(const std::string& name);

    void SetVolumeSFX(const std::string& name, int volume);
    void SetVolumeMusic(const std::string& name, int volume);

    void SetVolumeAllSFX(int volume);
    void SetVolumeAllMusic(int volume);

    void updateVolumeSFX(const std::string& name);
    void updateVolumeMusic(const std::string& name);

    void updateVolumeAllSFX();
    void updateVolumeAllMusic();

    void update();

    void Cleanup();

    void setMasterVolume(float volume);
    void setMusicVolume(float volume);
    void setSoundEffectVolume(float volume);
    void setAmbientVolume(float volume);

    float getMasterVolume() const;
    float getMusicVolume() const;
    float getSoundEffectVolume() const;
    float getAmbientVolume() const;

    void StopAllSounds();

    static int toSDLVolume(float vol) {
        return lerp(0, 30, vol);
    }

    void saveVolumeToFile();
    void loadVolumeFromFile();

};

