#pragma once
#include "Level.h"
#include "Enemy.h"
#include "Ziz.h"
#include "Player.h"
#include "Gust.h"
#include "StormRise.h"

#include <list>


class LevelBossTest : public Level
{
private:
	list<DrawableObject*> objectsList;
	float timeK = 0;
	float dt = 0;
	Ziz* ziz;
	Player* player;
	Gust* gust;
	StormRise* stormRise;

public:
	virtual void levelLoad();
	virtual void levelInit();
	virtual void levelUpdate();
	virtual void levelDraw();
	virtual void levelFree();
	virtual void levelUnload();

	virtual void handleKey(char key);
	virtual void handleMouse(int type, int x, int y);
	virtual void handleAnalogStick(int type, float amount);

	virtual void addObject(DrawableObject* obj) override;
};
