#pragma once
#include "Level.h"
#include <list>

class LevelUITest : public Level
{
private:
    list<DrawableObject*> objectsList;
    PlayerObject* player;
    EnemyObject* enemy;
    TexturedObject* background;
    float zoomRatio = 0.05f;
    //Button* quitButton;

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
};
