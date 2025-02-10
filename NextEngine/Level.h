#pragma once
#include "GameEngine.h"
#include "SquareMeshVbo.h"
#include "SquareBorderMesh.h"
#include "SimpleObject.h"
#include "TexturedObject.h"
#include "Button.h"
#include "PlayerObject.h"
#include "EnemyObject.h"

class Level
{
private:
    list<DrawableObject*> objectsList;
    PlayerObject* player;
    EnemyObject* enemy;
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

    virtual void updateObjects(list<DrawableObject*>& objectsList);
    virtual void addObject(DrawableObject* obj);
};
