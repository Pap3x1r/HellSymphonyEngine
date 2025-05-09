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
	list<UIButton*> controlsButtons;
	list<UIButton*> creditsButton;

	float timeK = 0;
	float dt = 0;
	//UI
	SimpleObject* playerHealthBar;
	SimpleObject* playerUltimateBar;
	SimpleObject* witherHealthBar;
	SimpleObject* bossHealthBar;

	float playerTimeScale = 1.0f;

	float transitionTime = 0.0f;
	float transitionDuration = 1.0f;
	bool transitioning = false;

	MenuState currentMenuState = MenuState::MAIN;
	MenuState nextMenuState = MenuState::MAIN;

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

	void toBoss() {
		GameEngine::getInstance()->getStateController()->gameStateNext = GameState::GS_LEVEL2;
	}
};
