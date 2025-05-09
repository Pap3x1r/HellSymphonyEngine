#pragma once

#include "GameStateList.h"
#include "InputManager.h"

class Level;

class GameStateController {
private:
	Level* currentLevel;

public:
	GameState gameStateCurr;
	GameState gameStatePrev;
	GameState gameStateNext;

	GameStateController();
	void init(GameState gameStateInit);

	void loadLevel();
	void initLevel();
	void updateLevel();
	void drawLevel();
	void freelevel();
	void unloadLevel();
	void handleKeyLevel(char key);
	void handleControllerButtonLevel(SDL_GameControllerButton button);
	void handleMouseLevel(int type, int x, int y);
	void handleAnalogLevel(int type, char key);
	void handleNotReceivingInputs();

	Level* getLevel() const {
		return currentLevel;
	}
};