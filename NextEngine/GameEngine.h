#pragma once

#include <vector>
#include "DrawableObject.h"
#include "GLRenderer.h"
#include "GameStateController.h"
#include "Time.h"
#include "InputManager.h" 
#include "SDL_ttf.h"
#include "Audio.h"
#include "WeaponType.h"
#include "SoundManager.h"


class Player;

using namespace std;

class GameEngine {
	static GameEngine* instance;
	int winWidth, winHeight;
	
	GLRenderer *renderer;
	GameStateController* stateController;
	Time* time;
	InputManager* inputHandler;
	vector<string> texturePaths;
	//AudioEngine* audio;

	GameEngine();
public:

	bool isNewGame = false;
	glm::vec3 playerPos = glm::vec3(0.0f);

	static GameEngine* getInstance();
	GLRenderer * getRenderer();
	GameStateController* getStateController();
	Time* getTime();
	//AudioEngine* getAudio();
	InputManager* getInputHandler();// Getter for input handler
	void init(int width, int height);
	void setDrawArea(float left, float right, float bottom, float top);
	void setBackgroundColor(float r, float g, float b);
	void addMesh(string name, MeshVbo* mesh);
	void clearMesh();
	void render(list<DrawableObject*> renderObjects);
	int getWindowWidth();
	int getWindowHeight();
	void setWindowWidth(int w);
	void setWindowHeight(int h);
	void freezeGameForSecond(float duration);
	void savePlayerData(const Player* player, const std::string& filename);
	void savePlayerData(int currentHP, int witherHP, int lives, const std::string& filename);
	Player* loadPlayerData(const string& filepath);
	void saveGameState(GameState state, const std::string& filename);
	GameState loadGameState(const std::string& filename, bool newGame);
	void savePlayerWeaponType(Player* player, const std::string& filepath);
	WeaponType loadPlayerWeaponType(const std::string& filename, bool newGame);
};