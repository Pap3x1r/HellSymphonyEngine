#pragma once
#include "Level.h"
#include "Enemy.h"
#include "Ziz.h"
#include "Player.h"
#include "Gust.h"
#include "StormRise.h"
#include "ChompTentacle.h"
#include "InteractableObject.h"

#include "PortalState.h"

#include "Sword.h"
#include "Bow.h"
#include "Shield.h"

#include "SwoopWarning.h"
#include "UltZizOnBG.h"
#include "Lightning.h"
#include "QTEButtonUI.h"
#include "Impale.h"

#include <list>


class LevelLimbo2 : public Level
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

	//Slider List
	list<SliderObject*> slidersList;

	SliderObject* masterSlider;
	SliderObject* musicSlider;
	SliderObject* sfxSlider;
	SliderObject* ambientSlider;


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



	////////////////////////////////////////////////////////////////




	list<DrawableObject*> objectsList;

	float timeK = 0;
	float dt = 0;

	Player* player;

	QTEButtonUI* qbui;

	InteractableObject* portal;
	InteractableObject* dummy;

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
	TexturedObject* tutorialOverlay = nullptr;

	TexturedObject* portal2 = nullptr;

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

	void toLoadingScreen() {
		GameStateController* gameStateController = GameEngine::getInstance()->getStateController();

		GameEngine::getInstance()->saveGameState(GameState::GS_LIMBO1, "../Resource/Saves/PlayerData/playerGameState.txt");
		GameEngine::getInstance()->savePlayerWeaponType(player, "../Resource/Saves/PlayerData/playerWeaponTypeData.txt");

		//Inserting directories to load and level destination
		gameStateController->pendingLoad.textureDirs = {};
		gameStateController->pendingLoad.nextStateAfterLoad = GameState::GS_MAINMENU;

		//Change to loading screen
		gameStateController->gameStateNext = GameState::GS_LOADINGSCREEN;
	}

	void previousLevel() {
		GameStateController* gameStateController = GameEngine::getInstance()->getStateController();
		//GameState targetGameState = GameEngine::getInstance()->loadGameState("../Resource/Saves/PlayerData/playerGameState.txt", 0);
		//Inserting directories to load and level destination
		GameEngine::getInstance()->savePlayerData(player, "../Resource/Saves/PlayerData/playerData.txt");
		GameEngine::getInstance()->savePlayerWeaponType(player, "../Resource/Saves/PlayerData/playerWeaponTypeData.txt");
		gameStateController->pendingLoad.textureDirs = {
		};
		gameStateController->pendingLoad.nextStateAfterLoad = GameState::GS_LIMBO1;
		GameEngine::getInstance()->isNewGame = false;
		GameEngine::getInstance()->playerPos = glm::vec3(7.5, -0.8f, 0.0f);

		gameStateController->gameStateNext = GameState::GS_LOADINGSCREEN;
	}

	void nextLevel() {
		GameStateController* gameStateController = GameEngine::getInstance()->getStateController();
		//GameState targetGameState = GameEngine::getInstance()->loadGameState("../Resource/Saves/PlayerData/playerGameState.txt", 0);
		//Inserting directories to load and level destination
		GameEngine::getInstance()->savePlayerData(player, "../Resource/Saves/PlayerData/playerData.txt");
		GameEngine::getInstance()->savePlayerWeaponType(player, "../Resource/Saves/PlayerData/playerWeaponTypeData.txt");
		gameStateController->pendingLoad.textureDirs = {
			"../Resource/Texture/Dante",
			"../Resource/Texture/Ziz",
			"../Resource/Texture/FinalZiz",
			"../Resource/Texture/FinalZiz/VFX"
		};
		gameStateController->pendingLoad.nextStateAfterLoad = GameState::GS_ZIZ;
		GameEngine::getInstance()->isNewGame = false;
		GameEngine::getInstance()->playerPos = glm::vec3(0.0f);

		gameStateController->gameStateNext = GameState::GS_LOADINGSCREEN;
	}

	void controllerUIHandling(SDL_GameControllerButton button);
};
