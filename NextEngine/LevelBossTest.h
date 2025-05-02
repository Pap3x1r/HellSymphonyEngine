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

#include <list>


class LevelBossTest : public Level
{
private:
	list<DrawableObject*> objectsList;
	list<UIButton*> buttonsList;
	float timeK = 0;
	float dt = 0;
	Ziz* ziz;
	Player* player;
	Gust* gust;
	StormRise* stormRise;
	ChompTentacle* chompTentacle;
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
	
	void addPlayerToDebug(Player* player);

	void resetLevel() {
		GameEngine::getInstance()->getStateController()->gameStateNext = GameState::GS_RESTART;
	}
};
