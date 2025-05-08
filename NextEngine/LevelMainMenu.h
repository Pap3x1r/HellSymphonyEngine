#pragma once
#include "Level.h"

#include <list>


class LevelMainMenu : public Level
{
private:
	list<DrawableObject*> objectsList;
	list<UIButton*> buttonsList;
	list<UIButton*> mainMenuButtons;
	list<UIButton*> optionButtons;
	float timeK = 0;
	float dt = 0;
	//UI
	SimpleObject* playerHealthBar;
	SimpleObject* playerUltimateBar;
	SimpleObject* witherHealthBar;
	SimpleObject* bossHealthBar;

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

	void resetLevel() {
		GameEngine::getInstance()->getStateController()->gameStateNext = GameState::GS_RESTART;
	}
};
