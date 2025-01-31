#pragma once

#include "Level.h"
#include "MapLoader.h"

class LevelMapEditorTest : public Level {
private:
    list<DrawableObject*> objectsList;
    DrawableObject* player;
    MapLoader mapLoader;
    TexturedObject* background;

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