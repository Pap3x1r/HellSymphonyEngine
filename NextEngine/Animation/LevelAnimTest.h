#pragma once
#include "../Level.h"

class LevelAnimTest : public Level
{
private:
	vector<DrawableObject*> objectsList;
	TexturedObject * player;
	int d = 0;
	int row = 0;
	int col = 0;
public:
	virtual void levelLoad();
	virtual void levelInit();
	virtual void levelUpdate();
	virtual void levelDraw();
	virtual void levelFree();
	virtual void levelUnload();

	virtual void handleKey(char key);
	virtual void handleMouse(int type, int x, int y);
};
