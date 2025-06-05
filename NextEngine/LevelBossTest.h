#pragma once
#include "Level.h"
#include "Enemy.h"
#include "Ziz.h"
#include "Player.h"
#include "Gust.h"
#include "StormRise.h"
#include "ChompTentacle.h"

#include "Sword.h"
#include "Bow.h"
#include "Shield.h"

#include "SwoopWarning.h"
#include "UltZizOnBG.h"
#include "Lightning.h"
#include "QTEButtonUI.h"
#include "Impale.h"

#include <list>


class LevelBossTest : public Level
{
private:

	///////////////////////////////////// Needed for UI ////////////////////////////////////////////
	UIButton* focusedButton = nullptr;
	int selectedIndex = -1; // Not select anything
	int hoveredIndex = -1; //Mouse
	bool controlByMouse = false;

	list<UIButton*> buttonsList;

	//Not for draw list
	list<UIButton*> mainButtons;
	list<UIButton*> pauseButtons;
	list<UIButton*> optionsButtons;
	list<UIButton*> audioButtons;
	list<UIButton*> controllerButtons;
	list<UIButton*> keyboardButtons;
	list<UIButton*> creditsButton;
	list<UIButton*> quitConfirmButtons;


	list<UIButton*> deathButtons;
	list<UIButton*> victoryButtons;

	//Slider List
	list<SliderObject*> slidersList;

	SliderObject* masterSlider;
	SliderObject* musicSlider;
	SliderObject* sfxSlider;
	SliderObject* ambientSlider;

	TexturedObject* lifeIcon1 = nullptr;
	TexturedObject* lifeIcon2 = nullptr;
	TexturedObject* lifeIcon3 = nullptr;

	UIButton* focusedHandle = nullptr;

	//UI
	TexturedObject* controllerOverlay = nullptr;
	TexturedObject* kbOverlay = nullptr;

	float transitionTime = 0.0f;
	float transitionDuration = 0.2f;
	bool transitioning = false;
	float holdButtonTimer = 0.0f;
	float holdButtonThreshold = 0.5f;


	float blackFadeTransitionTime = 0.0f;
	float blackFadeTransitionDuration = 1.0f;
	bool firstStart = true;
	TexturedObject* blackFade = nullptr;

	MenuState currentMenuState = MenuState::MAIN;
	MenuState nextMenuState = MenuState::MAIN;

	bool isHolding;

	bool levelEnd = false;


	////////////////////////////////////////////////////////////////




	list<DrawableObject*> objectsList;

	float timeK = 0;
	float dt = 0;
	Ziz* ziz;
	Player* player;
	Gust* gust;
	StormRise* stormRise;
	ChompTentacle* chompTentacle;
	QTEButtonUI* qbui;

	//ControlType
	InputManager* inputManager;

	enum ControlType {
		keyboard = 0,
		controller
	};

	ControlType currentControlType = ControlType::keyboard;

	//UI
	SimpleObject* playerHealthBar;
	SimpleObject* playerUltimateBar;
	SimpleObject* witherHealthBar;
	SimpleObject* bossHealthBar;
	SimpleObject* playerOverheatBar;

	TexturedObject* playerOverheatBarBackground = nullptr;
	TexturedObject* playerOverheatBarFrame = nullptr;

	//Skill Icon
	TexturedObject* bowSmallUltIconOff = nullptr;
	TexturedObject* bowSmallUltIconOn = nullptr;
	TexturedObject* bowBigUltIconOff = nullptr;
	TexturedObject* bowBigUltIconOn = nullptr;

	TexturedObject* swordSmallUltIconOff = nullptr;
	TexturedObject* swordSmallUltIconOn = nullptr;
	TexturedObject* swordBigUltIconOff = nullptr;
	TexturedObject* swordBigUltIconOn = nullptr;

	TexturedObject* shieldSmallUltIconOff = nullptr;
	TexturedObject* shieldSmallUltIconOn = nullptr;
	TexturedObject* shieldBigUltIconOff = nullptr;
	TexturedObject* shieldBigUltIconOn = nullptr;

	TexturedObject* dashIcon = nullptr;

	void createSkillsIcon();
	void updateSkillsIcon();
	void playerUltimateInput();
	void updateUIBar();
	void stateMachineUpdate(float dt);

	float playerTimeScale = 1.0f;

	int tempx;
	int tempx2;

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
	virtual void isReceivingNoInputs();
	

	virtual void addObject(DrawableObject* obj) override;
	
	void addPlayerToDebug(Player* player);

	void resetLevel() {
		GameEngine::getInstance()->getStateController()->gameStateNext = GameState::GS_RESTART;
	}

	bool isPausing(float dt);

	void changeMenuState(MenuState targetState);
	MenuState getMenuState() const;

	void mouseUIHandling(int type, float x, float y);
	void keyboardUIHandling(char key);

	glm::vec2 convertMouseToGameSpace(int mouseX, int mouseY);

	void changeSelection(int direction);

	void buttonsFree();

	void UIUpdate();

	void switchControlType(ControlType ct);

	void createPauseUI();

	void toLoadingScreenDeath() {
		GameStateController* gameStateController = GameEngine::getInstance()->getStateController();

		if (player->getLives() > 1) {
			GameEngine::getInstance()->saveGameState(GameEngine::getInstance()->getStateController()->gameStateCurr, "../Resource/Saves/PlayerData/playerGameState.txt");
			GameEngine::getInstance()->savePlayerWeaponType(player, "../Resource/Saves/PlayerData/playerWeaponTypeData.txt");
			GameEngine::getInstance()->savePlayerData(100, 0, player->getLives() - 1, "../Resource/Saves/PlayerData/playerData.txt");
		}
		else {
			GameEngine::getInstance()->saveGameState(GS_LIMBO1, "../Resource/Saves/PlayerData/playerGameState.txt");
			GameEngine::getInstance()->savePlayerWeaponType(player, "../Resource/Saves/PlayerData/playerWeaponTypeData.txt");
			GameEngine::getInstance()->savePlayerData(100, 0, 3, "../Resource/Saves/PlayerData/playerData.txt");
		}

		//Inserting directories to load and level destination
		gameStateController->pendingLoad.textureDirs = {};
		gameStateController->pendingLoad.nextStateAfterLoad = GameState::GS_MAINMENU;

		//Change to loading screen
		gameStateController->gameStateNext = GameState::GS_LOADINGSCREEN;
	}

	void toLoadingScreenVictory() {
		GameStateController* gameStateController = GameEngine::getInstance()->getStateController();

		GameEngine::getInstance()->saveGameState(GameState::GS_LUCIFER, "../Resource/Saves/PlayerData/playerGameState.txt");
		GameEngine::getInstance()->savePlayerWeaponType(player, "../Resource/Saves/PlayerData/playerWeaponTypeData.txt");
		GameEngine::getInstance()->savePlayerData(100, 0, player->getLives(), "../Resource/Saves/PlayerData/playerData.txt");

		//Inserting directories to load and level destination
		gameStateController->pendingLoad.textureDirs = {};
		gameStateController->pendingLoad.nextStateAfterLoad = GameState::GS_MAINMENU;

		//Change to loading screen
		gameStateController->gameStateNext = GameState::GS_LOADINGSCREEN;
	}

	void toLoadingScreen() {
		GameStateController* gameStateController = GameEngine::getInstance()->getStateController();

		GameEngine::getInstance()->saveGameState(gameStateController->gameStateCurr, "../Resource/Saves/PlayerData/playerGameState.txt");
		GameEngine::getInstance()->savePlayerWeaponType(player, "../Resource/Saves/PlayerData/playerWeaponTypeData.txt");
		GameEngine::getInstance()->savePlayerData(100, 0, player->getLives(), "../Resource/Saves/PlayerData/playerData.txt");

		//Inserting directories to load and level destination
		gameStateController->pendingLoad.textureDirs = {};
		gameStateController->pendingLoad.nextStateAfterLoad = GameState::GS_MAINMENU;

		//Change to loading screen
		gameStateController->gameStateNext = GameState::GS_LOADINGSCREEN;
	}

	void nextLevel() {
		GameStateController* gameStateController = GameEngine::getInstance()->getStateController();

		GameEngine::getInstance()->saveGameState(GS_LUCIFER, "../Resource/Saves/PlayerData/playerGameState.txt");
		GameEngine::getInstance()->savePlayerWeaponType(player, "../Resource/Saves/PlayerData/playerWeaponTypeData.txt");
		GameEngine::getInstance()->savePlayerData(100, 0, player->getLives(), "../Resource/Saves/PlayerData/playerData.txt");

		//Inserting directories to load and level destination
		gameStateController->pendingLoad.textureDirs = {};
		gameStateController->pendingLoad.nextStateAfterLoad = GameState::GS_LUCIFER;

		//Change to loading screen
		gameStateController->gameStateNext = GameState::GS_LOADINGSCREEN;
	}

	void retryLevel() {
		GameStateController* gameStateController = GameEngine::getInstance()->getStateController();

		GameEngine::getInstance()->saveGameState(GameEngine::getInstance()->getStateController()->gameStateCurr, "../Resource/Saves/PlayerData/playerGameState.txt");
		GameEngine::getInstance()->savePlayerWeaponType(player, "../Resource/Saves/PlayerData/playerWeaponTypeData.txt");
		GameEngine::getInstance()->savePlayerData(100, 0, player->getLives() - 1, "../Resource/Saves/PlayerData/playerData.txt");

		//Inserting directories to load and level destination
		gameStateController->pendingLoad.textureDirs = {};
		gameStateController->pendingLoad.nextStateAfterLoad = GameEngine::getInstance()->getStateController()->gameStateCurr;

		//Change to loading screen
		gameStateController->gameStateNext = GameState::GS_LOADINGSCREEN;
	}

	void resurrect() {
		GameStateController* gameStateController = GameEngine::getInstance()->getStateController();

		GameEngine::getInstance()->saveGameState(GS_LIMBO1, "../Resource/Saves/PlayerData/playerGameState.txt");
		GameEngine::getInstance()->savePlayerWeaponType(player, "../Resource/Saves/PlayerData/playerWeaponTypeData.txt");
		GameEngine::getInstance()->savePlayerData(100, 0, 3, "../Resource/Saves/PlayerData/playerData.txt");

		GameEngine::getInstance()->isNewGame = true;

		//Inserting directories to load and level destination
		gameStateController->pendingLoad.textureDirs = {};
		gameStateController->pendingLoad.nextStateAfterLoad = GS_LIMBO1;

		//Change to loading screen
		gameStateController->gameStateNext = GameState::GS_LOADINGSCREEN;
	}

	void exitDeath() {
		GameStateController* gameStateController = GameEngine::getInstance()->getStateController();

		if (player->getLives() - 1 == 0) { // Reset
			GameEngine::getInstance()->saveGameState(GS_LIMBO1, "../Resource/Saves/PlayerData/playerGameState.txt");
			GameEngine::getInstance()->savePlayerWeaponType(player, "../Resource/Saves/PlayerData/playerWeaponTypeData.txt");
			GameEngine::getInstance()->savePlayerData(100, 0, 3, "../Resource/Saves/PlayerData/playerData.txt");
		}
		else {
			GameEngine::getInstance()->saveGameState(GameEngine::getInstance()->getStateController()->gameStateCurr, "../Resource/Saves/PlayerData/playerGameState.txt");
			GameEngine::getInstance()->savePlayerWeaponType(player, "../Resource/Saves/PlayerData/playerWeaponTypeData.txt");
			GameEngine::getInstance()->savePlayerData(100, 0, player->getLives() - 1, "../Resource/Saves/PlayerData/playerData.txt");
		}

		//Inserting directories to load and level destination
		gameStateController->pendingLoad.textureDirs = {};
		gameStateController->pendingLoad.nextStateAfterLoad = GameEngine::getInstance()->getStateController()->gameStateCurr;

		//Change to loading screen
		gameStateController->gameStateNext = GameState::GS_QUIT;
	}

	void exitVictory() {
		GameStateController* gameStateController = GameEngine::getInstance()->getStateController();

		GameEngine::getInstance()->saveGameState(GameState::GS_LUCIFER, "../Resource/Saves/PlayerData/playerGameState.txt");
		GameEngine::getInstance()->savePlayerWeaponType(player, "../Resource/Saves/PlayerData/playerWeaponTypeData.txt");
		GameEngine::getInstance()->savePlayerData(100, 0, player->getLives(), "../Resource/Saves/PlayerData/playerData.txt");

		//Inserting directories to load and level destination
		gameStateController->pendingLoad.textureDirs = {};
		gameStateController->pendingLoad.nextStateAfterLoad = GameEngine::getInstance()->getStateController()->gameStateCurr;

		//Change to loading screen
		gameStateController->gameStateNext = GameState::GS_QUIT;
	}

	void controllerUIHandling(SDL_GameControllerButton button);
};
