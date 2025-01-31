#pragma once

#include "Level.h"
#include "MapLoader.h"
#include <list>

class LevelCollisionTest : public Level {
    private:
        list<DrawableObject*> objectsList;
        DrawableObject* player;
        DrawableObject* ground;
        TexturedObject* background;
        MapLoader mapLoader;

    public:
        virtual void levelLoad();
        virtual void levelInit();
        virtual void levelUpdate();
        virtual void levelDraw();
        virtual void levelFree();
        virtual void levelUnload();

        virtual void handleKey(char key);

        void handleMouse(int type, int x, int y) {} // temporary fix to disable mouse
};

void triggerTest(DrawableObject* obj1, DrawableObject* obj2);
void printCollisionState(DrawableObject* obj1, DrawableObject* obj2);