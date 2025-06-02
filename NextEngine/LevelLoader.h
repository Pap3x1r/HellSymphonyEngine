#pragma once
#include "Level.h"
#include <thread>
#include <atomic>

#include <list>
#include <vector>


class LevelLoader : public Level
{
private:
	list<DrawableObject*> objectsList;
	list<UIButton*> buttonsList;
	float timeK = 0;
	float dt = 0;

	TexturedObject* playerSpriteWalking = nullptr;

	float playerTimeScale = 1.0f;

	float blackFadeTransitionTime = 0.0f;
	float blackFadeTransitionDuration = 1.0f;
	bool firstStart = true;
	TexturedObject* blackFade = nullptr;

	

	bool texturesLoaded = false;

	int currentTextureIndex = 0;
	vector<string> textureDirsToLoad;
	vector<string> texturePathsToLoad;
	GameState nextState = GameState::GS_MAINMENU;

public:
	virtual void levelLoad();
	virtual void levelInit();
	virtual void levelUpdate();
	virtual void levelDraw();
	virtual void levelFree();
	virtual void levelUnload();

	virtual void handleKey(char key);
	virtual void handleControllerButton(SDL_GameControllerButton button);
	virtual void handleMouse(int type, int x, int y);
	virtual void handleAnalogStick(int type, char key);

	virtual void addObject(DrawableObject* obj) override;

	void resetLevel() {
		GameEngine::getInstance()->getStateController()->gameStateNext = GameState::GS_RESTART;
	}
	
	void configure(const std::vector<std::string>& dirs, GameState nextState_);
	void gatherTexturesFromDirs(const std::vector<std::string>& dirs);
	void loadOneTexturePerFrame();
};
