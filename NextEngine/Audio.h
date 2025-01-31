#pragma once

#include <SDL_mixer.h>
#include <string>
#include <map>
#include <vector>

class SoundEffect {
public:
	friend class AudioEngine;
	void play(int loop = 0);
private:
	Mix_Chunk* m_chunk = nullptr;
};

class Music {
public:
	friend class AudioEngine;
	void play(int loop = 0);
	void pause();
	void stop();
	void resume();
private:
	Mix_Music* m_music = nullptr;
};

struct SoundEffectObj {
	std::string fileName;
	SoundEffect soundEffect;
};

struct MusicObj {
	std::string fileName;
	Music music;
};

class AudioEngine {
public:
	AudioEngine();
	~AudioEngine();

	void init(const std::string& effectFolderPath, const std::string& musicFolderPath);
	void destroy();

	SoundEffect loadSoundEffect(const std::string& filePath);
	void playSoundEffectByIndex(int index, int loop = 0);
	void playSoundEffectByName(const std::string& fileName, int loop = 0);


	Music loadMusic(const std::string& filePath);
	void playMusicByIndex(int index, int loop = 0);
	void playMusicByName(const std::string& fileName, int loop = 0);

	void stopMusic();

	void adjustSoundEffectVolume(int amount);
	void adjustMusicVolume(int amount);

	void setSoundEffectVolume(int value);
	void setMusicVolume(int value);

	void saveVolumeToFile();
	void printVolume();
private:
	bool isInit = false;
	int currentSoundEffectVolume;
	int currentMusicVolume;

	std::vector<SoundEffectObj> v_soundEffect;
	std::vector<MusicObj> v_music;

	std::map<std::string, Mix_Chunk*> m_effectMap;
	std::map<std::string, Mix_Music*> m_musicMap;

	void loadSoundEffectFromDir(const std::string& dir);
	void loadMusicFromDir(const std::string& dir);
};