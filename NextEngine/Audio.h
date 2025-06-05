//#pragma once
//#include <filesystem>
//#include <SDL_mixer.h>
//#include <string>
//#include <map>
//#include <vector>
//
//class SoundEffect {
//public:
//	friend class AudioEngine;
//	void play(int loop = 0);
//private:
//	Mix_Chunk* m_chunk = nullptr;
//};
//
//class Music {
//public:
//	friend class AudioEngine;
//	void play(int loop = 0);
//	void pause();
//	void stop();
//	void resume();
//private:
//	Mix_Music* m_music = nullptr;
//};
//
//struct SoundEffectObj {
//	std::string fileName;
//	SoundEffect soundEffect;
//	bool isAmbient = false;	
//};
//
//struct MusicObj {
//	std::string fileName;
//	Music music;
//	bool isAmbient = false;
//};
//
//class AudioEngine {
//public:
//	AudioEngine();
//	~AudioEngine();
//
//	void init(const std::string& effectFolderPath, const std::string& musicFolderPath);
//	void update();
//	void destroy();
//
//	SoundEffect loadSoundEffect(const std::string& filePath);
//	void playSoundEffectByIndex(int index, int loop = 0);
//	void playSoundEffectByName(const std::string& fileName, int loop = 0);
//
//
//	Music loadMusic(const std::string& filePath);
//	void playMusicByIndex(int index, int loop = 0);
//	void playMusicByName(const std::string& fileName, int loop = 0);
//
//	void stopMusic();
//
//	void adjustMasterVolume(float amount);
//	void adjustSoundEffectVolume(float amount);
//	void adjustMusicVolume(float amount);
//	void adjustAmbientVolume(float amount);
//
//	void setMasterVolume(float value);
//	void setSoundEffectVolume(float value);
//	void setMusicVolume(float value);
//	void setAmbientVolume(float value);
//
//	float getMasterVolume() const;
//	float getSoundEffectVolume() const;
//	float getMusicVolume() const;
//	float getAmbientVolume() const;
//
//	void saveVolumeToFile();
//	void printVolume();
//private:
//	bool isInit = false;
//
//	float currentMasterVolume;
//	float currentSoundEffectVolume;
//	float currentMusicVolume;
//	float currentAmbientVolume;
//
//	// Sound effects
//	std::vector<std::filesystem::directory_entry> soundEffectEntries;
//	size_t soundEffectLoadIndex = 0;
//	bool soundEffectsLoadingDone = false;
//
//	// Music
//	std::vector<std::filesystem::directory_entry> musicEntries;
//	size_t musicLoadIndex = 0;
//	bool musicLoadingDone = false;
//
//	const size_t filesToLoadPerFrame = 1; // Shared chunk size
//
//	std::vector<SoundEffectObj> v_soundEffect;
//	std::vector<MusicObj> v_music;
//
//	std::map<std::string, Mix_Chunk*> m_effectMap;
//	std::map<std::string, Mix_Music*> m_musicMap;
//
//	void loadSoundEffectFromDir(const std::string& dir);
//	void loadMusicFromDir(const std::string& dir);
//
//	void updateAllVolumes();
//	int convertVolume(float volume);
//
//	void initLoadSoundEffectsFromDir(const std::string& dir);
//	void initLoadMusicFromDir(const std::string& dir);
//	void loadSoundEffectsIncremental();
//	void loadMusicIncremental();
//};