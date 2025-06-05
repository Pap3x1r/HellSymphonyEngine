//#include "pch.h"
//#include "Audio.h"
//#include <iostream>
//#include <vector>
//#include <filesystem>	
//#include <fstream>
//
//#define MIX_MIN_VOLUME 0
//
//void SoundEffect::play(int loop)
//{
//	if (Mix_PlayChannel(-1, m_chunk, loop) == -1)
//	{
//		std::cout << "Mix_PlayChannel Error " << std::string(Mix_GetError());
//	}
//}
//
//void Music::play(int loop)
//{
//	Mix_PlayMusic(m_music, loop);
//}
//
//void Music::pause()
//{
//	Mix_PauseMusic();
//}
//
//void Music::stop()
//{
//	Mix_HaltMusic();
//}
//
//void Music::resume()
//{
//	Mix_ResumeMusic();
//}
//
//AudioEngine::AudioEngine()
//{
//	std::ifstream volumeFile("../Resource/Audio/volumeFile.txt");
//
//	if (volumeFile.is_open()) {
//		volumeFile >> currentMasterVolume >> currentSoundEffectVolume >> currentMusicVolume >> currentAmbientVolume;
//
//		/*if (!(currentSoundEffectVolume >= MIX_MIN_VOLUME && currentSoundEffectVolume <= MIX_MAX_VOLUME) && (currentMusicVolume >= MIX_MIN_VOLUME && currentMusicVolume <= MIX_MAX_VOLUME)) {
//			currentSoundEffectVolume = MIX_MAX_VOLUME / 2;
//			currentMusicVolume = MIX_MAX_VOLUME / 2;
//
//			std::cerr << "Error: Volume file has invalid volume, setting back to default values" << std::endl;
//		}*/
//
//		currentMasterVolume = std::clamp(currentMasterVolume, 0.0f, 1.0f);
//		currentSoundEffectVolume = std::clamp(currentSoundEffectVolume, 0.0f, 1.0f);
//		currentMusicVolume = std::clamp(currentMusicVolume, 0.0f, 1.0f);
//		currentAmbientVolume = std::clamp(currentAmbientVolume, 0.0f, 1.0f);
//
//		std::cout << "Loaded master volume: " << currentMasterVolume << std::endl;
//		std::cout << "Loaded sound effect volume: " << currentSoundEffectVolume << std::endl;
//		std::cout << "Loaded music volume: " << currentMusicVolume << std::endl;
//		std::cout << "Loaded ambient volume: " << currentAmbientVolume << std::endl;
//
//		volumeFile.close();
//	}
//	else {
//		std::ofstream newVolumeFile("../Resource/Audio/volumeFile.txt");
//		if (newVolumeFile.is_open()) {
//			currentMasterVolume = 1.0f;
//			currentSoundEffectVolume = 1.0f;
//			currentMusicVolume = 1.0f;
//			currentAmbientVolume = 1.0f;
//
//			newVolumeFile << currentMasterVolume << "\n" << currentSoundEffectVolume << "\n" << currentMusicVolume << "\n" << currentAmbientVolume << "\n";
//			newVolumeFile.close();
//
//			std::cout << "Created new volume file" << std::endl;
//		}
//		else {
//			std::cerr << "Error: Could not create volume file" << std::endl;
//		}
//	}
//}
//
//AudioEngine::~AudioEngine()
//{
//}
//
//void AudioEngine::init(const std::string& effectFolderPath, const std::string& musicFolderPath)
//{
//	if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == -1)
//	{
//		std::cout << "Mix_Init Error " << std::string(Mix_GetError());
//	}
//
//	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
//	{
//		std::cout << "Mix_Init Error " << std::string(Mix_GetError());
//	}
//
//	/*Mix_Volume(-1, currentSoundEffectVolume);
//	Mix_VolumeMusic(currentMusicVolume);*/
//
//	//loadSoundEffectFromDir(effectFolderPath);
//	//loadMusicFromDir(musicFolderPath);
//
//	//initLoadSoundEffectsFromDir(effectFolderPath);
//	//initLoadMusicFromDir(musicFolderPath);
//
//	isInit = true;
//}
//
//void AudioEngine::destroy()
//{
//	if (isInit)
//	{
//		isInit = false;
//		Mix_Quit();
//	}
//}
//
//SoundEffect AudioEngine::loadSoundEffect(const std::string& filePath)
//{
//	//Try to find sound in cache
//	auto it = m_effectMap.find(filePath);
//
//	SoundEffect effect;
//
//	if (it == m_effectMap.end())
//	{
//		//Not found sound in cache
//		Mix_Chunk* chunk = Mix_LoadWAV(filePath.c_str());
//		if (chunk == nullptr)
//		{
//			std::cout << "Mix_LoadWAV Error " << std::string(Mix_GetError());
//		}
//		effect.m_chunk = chunk;
//		m_effectMap[filePath] = chunk;
//	}
//	else
//	{
//		//Find sound in cache
//		effect.m_chunk = it->second;
//	}
//
//
//	return effect;
//}
//
//void AudioEngine::playSoundEffectByIndex(const int index, int loop) {
//
//	//std::cout << "Attempting to play sound effect at index: " << index << std::endl;
//	//std::cout << "Current sound effect vector size: " << v_soundEffect.size() << std::endl;
//
//	if (index >= 0 && index < v_soundEffect.size()) {
//		SoundEffect soundEffect = v_soundEffect[index].soundEffect;
//		soundEffect.play(loop);
//	}
//	else {
//		std::cerr << "Error: Invalid sound effect index, Given: " << index << " Expected: 0 - " << v_soundEffect.size() - 1 << std::endl;
//	}
//}
//
//void AudioEngine::playSoundEffectByName(const std::string& fileName, int loop) {
//	for (auto& item : v_soundEffect) {
//		if (item.fileName == fileName) {
//			item.soundEffect.play(loop);
//			return;
//		}
//	}
//	std::cerr << "Error: " << fileName << " can't be found in sound effect" << std::endl;
//}
//
//Music AudioEngine::loadMusic(const std::string& filePath)
//{
//	//Try to find sound in cache
//	auto it = m_musicMap.find(filePath);
//
//	Music music;
//
//	if (it == m_musicMap.end())
//	{
//		//Not found sound in cache
//		Mix_Music* mixMusic = Mix_LoadMUS(filePath.c_str());
//		if (mixMusic == nullptr)
//		{
//			std::cout << "Mix_LoadMUS Error " << std::string(Mix_GetError());
//		}
//		music.m_music = mixMusic;
//		m_musicMap[filePath] = mixMusic;
//	}
//	else
//	{
//		//Find sound in cache
//		music.m_music = it->second;
//	}
//
//
//	return music;
//}
//
//void AudioEngine::playMusicByIndex(int index, int loop) {
//	if (index >= 0 && index < v_music.size()) {
//		Music music = v_music[index].music;
//		music.play(loop);
//	}
//	else {
//		std::cerr << "Error: Invalid music index, Given: " << index << " Expected: 0 - " << v_music.size() - 1 << std::endl;
//	}
//}
//
//void AudioEngine::playMusicByName(const std::string& fileName, int loop) {
//	for (auto& item : v_music) {
//		if (item.fileName == fileName) {
//			item.music.play(loop);
//			return;
//		}
//	}
//	std::cerr << "Error: " << fileName << " can't be found in music" << std::endl;
//}
//
//void AudioEngine::loadSoundEffectFromDir(const std::string& dir) {
//	for (const auto& paths : std::filesystem::directory_iterator(dir)) {
//		if (paths.is_regular_file()) {
//			std::string filePath = paths.path().string();
//			std::string fileName = paths.path().filename().string();
//
//			SoundEffect soundEffect = loadSoundEffect(filePath);
//
//			bool isAmbient = fileName.find("ambient") != std::string::npos;
//
//			v_soundEffect.push_back({ fileName, soundEffect, isAmbient });
//
//			std::cout << "Added " << fileName
//				<< " (ambient: " << std::boolalpha << isAmbient << ") "
//				<< "to sound effect vector at index: "
//				<< v_soundEffect.size() - 1 << std::endl;
//		}
//		else {
//			std::cerr << "Error: path is not a file. Path:" << paths.path().string() << std::endl;
//		}
//	}
//}
//
//void AudioEngine::initLoadSoundEffectsFromDir(const std::string& dir) {
//	soundEffectEntries.clear();
//	soundEffectLoadIndex = 0;
//	soundEffectsLoadingDone = false;
//
//	try {
//		for (const auto& entry : std::filesystem::directory_iterator(dir)) {
//			if (entry.is_regular_file()) {
//				soundEffectEntries.push_back(entry);
//			}
//		}
//	}
//	catch (const std::filesystem::filesystem_error& e) {
//		std::cerr << "Filesystem error: " << e.what() << std::endl;
//		std::cerr << "Failed to open directory: " << dir << std::endl;
//	}
//}
//
//void AudioEngine::initLoadMusicFromDir(const std::string& dir) {
//	musicEntries.clear();
//	musicLoadIndex = 0;
//	musicLoadingDone = false;
//
//	for (const auto& entry : std::filesystem::directory_iterator(dir)) {
//		if (entry.is_regular_file()) {
//			musicEntries.push_back(entry);
//		}
//	}
//}
//
//void AudioEngine::loadSoundEffectsIncremental() {
//	if (soundEffectsLoadingDone) return;
//
//	size_t count = 0;
//	while (soundEffectLoadIndex < soundEffectEntries.size() && count < filesToLoadPerFrame) {
//		const auto& entry = soundEffectEntries[soundEffectLoadIndex];
//		std::string filePath = entry.path().string();
//		std::string fileName = entry.path().filename().string();
//
//		SoundEffect soundEffect = loadSoundEffect(filePath);
//		bool isAmbient = fileName.find("ambient") != std::string::npos;
//
//		v_soundEffect.push_back({ fileName, soundEffect, isAmbient });
//		std::cout << "Loaded SFX: " << fileName << (isAmbient ? " (ambient)" : "") << std::endl;
//
//		soundEffectLoadIndex++;
//		count++;
//	}
//
//	if (soundEffectLoadIndex >= soundEffectEntries.size()) {
//		soundEffectsLoadingDone = true;
//		soundEffectEntries.clear();
//	}
//}
//
//void AudioEngine::loadMusicIncremental() {
//	if (musicLoadingDone) return;
//
//	size_t count = 0;
//	while (musicLoadIndex < musicEntries.size() && count < filesToLoadPerFrame) {
//		const auto& entry = musicEntries[musicLoadIndex];
//		std::string filePath = entry.path().string();
//		std::string fileName = entry.path().filename().string();
//
//		Music music = loadMusic(filePath);
//		bool isAmbient = fileName.find("ambient") != std::string::npos;
//
//		v_music.push_back({ fileName, music, isAmbient });
//		std::cout << "Loaded Music: " << fileName << (isAmbient ? " (ambient)" : "") << std::endl;
//
//		musicLoadIndex++;
//		count++;
//	}
//
//	if (musicLoadIndex >= musicEntries.size()) {
//		musicLoadingDone = true;
//		musicEntries.clear();
//	}
//}
//
//void AudioEngine::loadMusicFromDir(const std::string& dir) {
//	for (const auto& paths : std::filesystem::directory_iterator(dir)) {
//		if (paths.is_regular_file()) {
//			std::string filePath = paths.path().string();
//			std::string fileName = paths.path().filename().string();
//
//			Music music = loadMusic(filePath);
//
//			bool isAmbient = fileName.find("ambient") != std::string::npos;
//
//			v_music.push_back({ fileName, music, isAmbient });
//
//			std::cout << "Added " << fileName
//				<< " (ambient: " << std::boolalpha << isAmbient << ") "
//				<< "to music vector at index: "
//				<< v_music.size() - 1 << std::endl;
//		}
//		else {
//			std::cerr << "Error: path is not a file. Path:" << paths.path().string() << std::endl;
//		}
//	}
//}
//
//
//
//void AudioEngine::adjustMasterVolume(float amount) {
//	currentMasterVolume += amount;
//	currentMasterVolume = std::clamp(currentMasterVolume, 0.0f, 1.0f);
//	updateAllVolumes();
//}
//
//void AudioEngine::adjustSoundEffectVolume(float amount) {
//	currentSoundEffectVolume += amount;
//	currentSoundEffectVolume = std::clamp(currentSoundEffectVolume, 0.0f, 1.0f);
//	updateAllVolumes();
//	/*int currentVolume = Mix_Volume(-1, -1);
//	int newVolume;
//
//	if (currentVolume + amount < MIX_MIN_VOLUME) {
//		newVolume = MIX_MIN_VOLUME;
//	}
//	else if (currentVolume + amount > MIX_MAX_VOLUME) {
//		newVolume = MIX_MAX_VOLUME;
//	}
//	else {
//		newVolume = currentVolume + amount;
//	}
//
//	currentSoundEffectVolume = newVolume;
//	Mix_Volume(-1, newVolume);
//	std::cout << "New sound effect volume: " << currentSoundEffectVolume << std::endl;*/
//}
//
//void AudioEngine::adjustMusicVolume(float amount) {
//	currentMusicVolume += amount;
//	currentMusicVolume = std::clamp(currentMusicVolume, 0.0f, 1.0f);
//	updateAllVolumes();
//	/*int currentVolume = Mix_VolumeMusic(-1);
//	int newVolume;
//
//	if (currentVolume + amount < MIX_MIN_VOLUME) {
//		newVolume = MIX_MIN_VOLUME;
//	}
//	else if (currentVolume + amount > MIX_MAX_VOLUME) {
//		newVolume = MIX_MAX_VOLUME;
//	}
//	else {
//		newVolume = currentMusicVolume + amount;
//	}
//
//	currentMusicVolume = newVolume;
//	Mix_VolumeMusic(newVolume);
//	std::cout << "New music volume: " << currentMusicVolume << std::endl;*/
//}
//
//void AudioEngine::adjustAmbientVolume(float amount) {
//	currentAmbientVolume += amount;
//	currentAmbientVolume = std::clamp(currentAmbientVolume, 0.0f, 1.0f);
//	updateAllVolumes();
//}
//
//void AudioEngine::setMasterVolume(float value) {
//	currentMasterVolume = std::clamp(value, 0.0f, 1.0f);
//	updateAllVolumes();
//}
//
//void AudioEngine::setSoundEffectVolume(float value) {
//	currentSoundEffectVolume = std::clamp(value, 0.0f, 1.0f);
//	updateAllVolumes();
//	/*if ((value >= 0) && (value <= 128)) {
//		Mix_Volume(-1, value);
//		currentSoundEffectVolume = value;
//		std::cout << "New sound effect volume: " << currentSoundEffectVolume << std::endl;
//		return;
//	}
//	std::cerr << "Error: set music volume is more than the maximum, Given: " << value << "Min,Max: 0,128 " << std::endl;*/
//}
//
//void AudioEngine::setMusicVolume(float value) {
//	currentMusicVolume = std::clamp(value, 0.0f, 1.0f);
//	updateAllVolumes();
//	/*if ((value >= 0) && (value <= 128)) {
//		Mix_VolumeMusic(value);
//		currentMusicVolume = value;
//		std::cout << "New music volume: " << currentMusicVolume << std::endl;
//		return;
//	}
//	std::cerr << "Error: adjust music volume is more than the maximum, Given: " << value << "Min,Max: 0,128 " << std::endl;*/
//}
//
//void AudioEngine::setAmbientVolume(float value) {
//	currentAmbientVolume = std::clamp(value, 0.0f, 1.0f);
//	updateAllVolumes();
//}
//
//float AudioEngine::getMasterVolume() const {
//	return currentMasterVolume;
//}
//
//float AudioEngine::getSoundEffectVolume() const {
//	return currentSoundEffectVolume;
//}
//
//float AudioEngine::getMusicVolume() const {
//	return currentMusicVolume;
//}
//
//float AudioEngine::getAmbientVolume() const {
//	return currentAmbientVolume;
//}
//
//void AudioEngine::saveVolumeToFile() {
//	std::ofstream volumeFile("../Resource/Audio/volumeFile.txt");
//
//	if (volumeFile.is_open()) {
//		volumeFile << currentMasterVolume << "\n" << currentSoundEffectVolume << "\n" << currentMusicVolume << "\n" << currentAmbientVolume << "\n";
//		volumeFile.close();
//		std::cout << "Volume settings saved to ../Resource/Audio/volumeFile.txt" << std::endl;
//	}
//	else {
//		std::cerr << "Error: Could not save volume to file: ../Resource/Audio/volumeFile.txt" << std::endl;
//	}
//}
//
//void AudioEngine::printVolume() {
//	std::cout << "sound vfx: " << currentSoundEffectVolume << " music: " << currentMusicVolume << std::endl;
//}
//
//void AudioEngine::stopMusic() {
//	Music music;
//	music.stop();
//}
//
//void AudioEngine::updateAllVolumes() {
//	// Update sound effect volumes
//	for (SoundEffectObj& se : v_soundEffect) {
//		float finalVolume = currentMasterVolume * (se.isAmbient ? currentAmbientVolume : currentSoundEffectVolume);
//		Mix_VolumeChunk(se.soundEffect.m_chunk, convertVolume(finalVolume));
//	}
//
//	// Update music volume — only applies to the *currently playing music*
//	for (const MusicObj& musicObj : v_music) {	
//		if (Mix_PlayingMusic()) {
//			float finalVolume = currentMasterVolume * (musicObj.isAmbient ? currentAmbientVolume : currentMusicVolume);
//			Mix_VolumeMusic(convertVolume(finalVolume));
//			break; // SDL_mixer only supports one music track at a time
//		}
//	}
//}
//
//int AudioEngine::convertVolume(float volume) {
//	return static_cast<int>(std::clamp(volume, 0.0f, 1.0f) * 128.0f);
//}
//
//void AudioEngine::update() {
//	//loadSoundEffectsIncremental();
//	//loadMusicIncremental();
//
//	// Check when loading finishes
//	if (soundEffectsLoadingDone && musicLoadingDone) {
//		//std::cout << "All audio loaded." << std::endl;
//	}
//}