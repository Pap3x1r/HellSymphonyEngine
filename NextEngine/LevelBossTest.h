#pragma once
#include "Level.h"
#include "Enemy.h"


class LevelBossTest : public Level
{
private:
	list<DrawableObject*> objectsList;
	float timeK = 0;
	float dt = 0;

public:
	virtual void levelLoad();
	virtual void levelInit();
	virtual void levelUpdate();
	virtual void levelDraw();
	virtual void levelFree();
	virtual void levelUnload();

	virtual void handleKey(char key);
};
