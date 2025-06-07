#pragma once
#include <map>
#include <string>
#include "Music.h"
#include "SFX.h"
#include <algorithm>

/**
 * @brief Linearly interpolates between two integers based on t [0, 1].
 *
 * @param a Start value.
 * @param b End value.
 * @param t Interpolation factor (clamped between 0 and 1).
 * @return Interpolated value.
 */
inline int lerp(int a, int b, float t) {
    t = std::clamp(t, 0.0f, 1.0f);  // ensures it's between 0 and 1
    return static_cast<int>(a + (b - a) * t);
}

/**
 * @class SoundManager
 * @brief Singleton class responsible for managing music and sound effects.
 *
 * Handles loading, playing, stopping, and volume control of all audio assets,
 * including ambient sounds, music, and effects.
 */
class SoundManager {
private:

    static SoundManager* instance; ///< Singleton instance.

    std::map<std::string, Music*> musicSounds; ///< Stores loaded music tracks.
    std::map<std::string, SFX*> SFXSounds; ///< Stores loaded sound effects.

    float currentMasterVolume = 1.0f;
    float currentSoundEffectVolume = 1.0f;
    float currentMusicVolume = 1.0f;
    float currentAmbientVolume = 1.0f;

public:
    /**
     * @brief Constructor.
     */
    SoundManager();
    /**
     * @brief Destructor.
     */
    ~SoundManager();

    /**
     * @brief Retrieves the singleton instance.
     *
     * @return Pointer to the SoundManager instance.
     */
    static SoundManager* GetInstance();

    /**
     * @brief Loads a sound effect.
     *
     * @param name Identifier for the sound effect.
     * @param filePath Path to the audio file.
     * @param ambient Whether the sound is ambient (affected by ambient volume).
     */
    void LoadSFX(const std::string& name, const std::string& filePath, bool ambient);

    /**
     * @brief Loads a music track.
     *
     * @param name Identifier for the music.
     * @param filePath Path to the music file.
     * @param ambient Whether the music is ambient.
     */
    void LoadMusic(const std::string& name, const std::string& filePath, bool ambient);

    /**
     * @brief Plays a sound effect.
     *
     * @param name Sound effect name.
     * @param isloop Whether the sound should loop.
     */
    void PlaySFX(const std::string& name, bool isloop = false);

    /**
     * @brief Plays a music track.
     *
     * @param name Music track name.
     * @param isloop Whether the music should loop.
     */
    void PlayMusic(const std::string& name, bool isloop = true);

    /**
     * @brief Stops a sound effect.
     *
     * @param name Sound effect name.
     */
    void StopSFX(const std::string& name);

    /**
     * @brief Stops a music track.
     *
     * @param name Music track name.
     */
    void StopMusic(const std::string& name);

    /**
     * @brief Sets the volume of a specific sound effect.
     *
     * @param name Sound effect name.
     * @param volume Volume (0-128 or SDL scale).
     */
    void SetVolumeSFX(const std::string& name, int volume);

    /**
     * @brief Sets the volume of a specific music track.
     *
     * @param name Music track name.
     * @param volume Volume (0-128 or SDL scale).
     */
    void SetVolumeMusic(const std::string& name, int volume);

    /**
     * @brief Sets volume for all sound effects.
     *
     * @param volume Volume (0-128 or SDL scale).
     */
    void SetVolumeAllSFX(int volume);

    /**
     * @brief Sets volume for all music tracks.
     *
     * @param volume Volume (0-128 or SDL scale).
     */
    void SetVolumeAllMusic(int volume);

    /**
     * @brief Updates volume of a specific sound effect based on current settings.
     *
     * @param name Sound effect name.
     */
    void updateVolumeSFX(const std::string& name);

    /**
     * @brief Updates volume of a specific music track based on current settings.
     *
     * @param name Music track name.
     */
    void updateVolumeMusic(const std::string& name);

    /**
     * @brief Updates volume of all sound effects.
     */
    void updateVolumeAllSFX();

    /**
     * @brief Updates volume of all music tracks.
     */
    void updateVolumeAllMusic();

    /**
     * @brief Called every frame to update volume levels or internal logic.
     */
    void update();

    /**
     * @brief Frees resources and clears loaded sounds.
     */
    void Cleanup();

    /**
     * @brief Sets the master volume (affects all sound types).
     * 
     * @param volume Float between 0.0f and 1.0f.
     */
    void setMasterVolume(float volume);

    /**
     * @brief Sets music-specific volume multiplier.
     * 
     * @param volume Float between 0.0f and 1.0f.
     */
    void setMusicVolume(float volume);

    /**
     * @brief Sets SFX-specific volume multiplier.
     * 
     * @param volume Float between 0.0f and 1.0f.
     */
    void setSoundEffectVolume(float volume);

    /**
     * @brief Sets ambient sound volume.
     * 
     * @param volume Float between 0.0f and 1.0f.
     */
    void setAmbientVolume(float volume);

    /**
     * @brief Gets the current master volume.
     * 
     * @return Master volume (0.0f - 1.0f).
     */
    float getMasterVolume() const;

    /**
     * @brief Gets the music volume multiplier.
     * 
     * @return Music volume (0.0f - 1.0f).
     */
    float getMusicVolume() const;

    /**
     * @brief Gets the SFX volume multiplier.
     * 
     * @return SFX volume (0.0f - 1.0f).
     */
    float getSoundEffectVolume() const;

    /**
     * @brief Gets the ambient volume multiplier.
     * 
     * @return Ambient volume (0.0f - 1.0f).
     */
    float getAmbientVolume() const;

    /**
     * @brief Stops all currently playing sounds.
     */
    void StopAllSounds();

    /**
     * @brief Converts normalized volume (0.0f to 1.0f) to SDL volume scale.
     * 
     * @param vol Float volume (0.0f - 1.0f).
     * @return Integer SDL volume (0 - 30).
     */
    static int toSDLVolume(float vol) {
        return lerp(0, 30, vol);
    }

    /**
     * @brief Saves volume settings to a file.
     */
    void saveVolumeToFile();

    /**
     * @brief Loads volume settings from a file.
     */
    void loadVolumeFromFile();

};

