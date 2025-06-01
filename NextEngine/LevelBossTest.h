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

	void createSkillsIcon();
	void updateSkillsIcon();
	void playerUltimateInput();

	float playerTimeScale = 1.0f;

	float blackFadeTransitionTime = 0.0f;
	float blackFadeTransitionDuration = 1.0f;
	bool firstStart = true;
	TexturedObject* blackFade = nullptr;


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
