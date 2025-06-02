#pragma once
#include "Level.h"


#include <list>


class LevelMainMenu : public Level
{
private:
	UIButton* focusedButton = nullptr;
	int selectedIndex = -1; // Not select anything
	int hoveredIndex = -1; //Mouse
	bool controlByMouse = false;

	list<DrawableObject*> objectsList;
	list<UIButton*> buttonsList;

	//Not for draw list
	list<UIButton*> mainButtons;
	list<UIButton*> optionsButtons;
	list<UIButton*> audioButtons;
	list<UIButton*> controllerButtons;
	list<UIButton*> keyboardButtons;
	list<UIButton*> creditsButton;

	//Slider List
	list<SliderObject*> slidersList;

	SliderObject* masterSlider;
	SliderObject* musicSlider;
	SliderObject* sfxSlider;
	SliderObject* ambientSlider;


	UIButton* focusedHandle = nullptr;

	float timeK = 0;
	float dt = 0;
	//UI
	
	TexturedObject* controllerOverlay = nullptr;
	TexturedObject* kbOverlay = nullptr;

	float playerTimeScale = 1.0f;

	float transitionTime = 0.0f;
	float transitionDuration = 0.5f;
	bool transitioning = false;
	float holdButtonTimer = 0.0f;
	float holdButtonThreshold = 0.5f;


	float blackFadeTransitionTime = 0.0f;
	float blackFadeTransitionDuration = 1.0f;
	bool firstStart = true;
	TexturedObject* blackFade = nullptr;

	MenuState currentMenuState = MenuState::MAIN;
	MenuState nextMenuState = MenuState::MAIN;

	//SliderObject* slider;

	bool isHolding;
	

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

	void resetLevel() {
		GameEngine::getInstance()->getStateController()->gameStateNext = GameState::GS_RESTART;
	}

	void changeMenuState(MenuState targetState) override;
	MenuState getMenuState() const override;

	void changeSelection(int direction);

	void toLoadingScreen() {
		GameStateController* gameStateController = GameEngine::getInstance()->getStateController();

		//Inserting directories to load and level destination
		gameStateController->pendingLoad.textureDirs = {
			"../Resource/Texture/Dante",
			"../Resource/Texture/Ziz",
			"../Resource/Texture/FinalZiz",
			"../Resource/Texture/FinalZiz/VFX"
		};
		gameStateController->pendingLoad.nextStateAfterLoad = GameState::GS_ZIZ;

		//Change to loading screen
		gameStateController->gameStateNext = GameState::GS_LOADINGSCREEN;
	}

	void quitGame() {
		GameEngine::getInstance()->getStateController()->gameStateNext = GameState::GS_QUIT;
	}

	glm::vec2 convertMouseToGameSpace(int mouseX, int mouseY);
};
