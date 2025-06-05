#include "GameStateController.h"
#include "Level.h"
#include "LevelParallax.h"
#include "LevelTest.h"
#include "LevelAnimTest.h"
#include "LevelCollisionTest.h"
#include "LevelUITest.h"
#include "LevelMapEditorTest.h"
#include "LevelPrototype.h"
#include "LevelBossTest.h"
#include "LevelLucifer.h"
#include "LevelMainMenu.h"
#include "LevelLoader.h"
#include "LevelLimbo1.h"
#include "LevelLimbo2.h"
#include "LevelCredits.h"

GameStateController::GameStateController() {
	// set the initial game state
	gameStateCurr = gameStatePrev = gameStateNext = GameState::GS_NONE;

	currentLevel = nullptr;
}

void GameStateController::init(GameState gameStateInit) {
	// reset the current, previoud and next game
	gameStateCurr = gameStatePrev = gameStateNext = gameStateInit;
}

void GameStateController::loadLevel() {
	if ((gameStateCurr == GameState::GS_RESTART) || (gameStateCurr == GameState::GS_QUIT)) {
		return;
	}
	cout << gameStateCurr << endl;
	switch (gameStateCurr) {
		case GameState::GS_MAINMENU:
			currentLevel = new LevelMainMenu();
			break;
		case GameState::GS_LOADINGSCREEN: {
			LevelLoader* loader = new LevelLoader();
			loader->configure(pendingLoad.textureDirs, pendingLoad.nextStateAfterLoad);
			currentLevel = loader;
			break;
		}
		case GameState::GS_LIMBO1:
			currentLevel = new LevelLimbo1();
			break;
		case GameState::GS_LIMBO2:
			currentLevel = new LevelLimbo2();
			break;
		case GameState::GS_ZIZ:
			currentLevel = new LevelBossTest();
			break;
		case GameState::GS_LUCIFER:
			currentLevel = new LevelLucifer();
			break;
		case GameState::GS_CREDITS:
			currentLevel = new LevelCredits();
			break;
		default:
			cout << "gameStateCurr : invalid state!!" << endl;
			exit(1);
	}

	currentLevel->levelLoad();
}

void GameStateController::initLevel() {
	currentLevel->levelInit();
}

void GameStateController::updateLevel() {
	currentLevel->levelUpdate();
}

void GameStateController::drawLevel() {
	currentLevel->levelDraw();
}

void GameStateController::freelevel() {
	currentLevel->levelFree();
}

void GameStateController::unloadLevel() {
	currentLevel->levelUnload();
}

void GameStateController::handleKeyLevel(char key) {
	currentLevel->handleKey(key);
}

void GameStateController::handleNotReceivingInputs() {
	currentLevel->isReceivingNoInputs();
}

void GameStateController::handleControllerButtonLevel(SDL_GameControllerButton button) {
	currentLevel->handleControllerButton(button);
}

void GameStateController::handleMouseLevel(int type, int x, int y) {
	currentLevel->handleMouse(type, x, y);
}

void GameStateController::handleAnalogLevel(int type, char key) {
	currentLevel->handleAnalogStick(type, key);
}