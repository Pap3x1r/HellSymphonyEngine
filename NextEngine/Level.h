#pragma once
#include "GameEngine.h"
#include "SoundManager.h"
#include "SquareMeshVbo.h"
#include "SquareBorderMesh.h"
#include "SimpleObject.h"
#include "TexturedObject.h"
#include "Button.h"
#include "SliderObject.h"
#include "PlayerObject.h"
#include "EnemyObject.h"
#include "Player.h"

#include "UIText.h"
#include "UIButton.h"

//imgui.h
#include <imgui.h>
#include <imgui_impl_opengl3.h>

class Level
{
private:
    list<DrawableObject*> objectsList;
    Player* player;
    EnemyObject* enemy;
    TexturedObject* background;

    float transitionTime = 0.0f;
    float transitionDuration = 1.0f;
    bool transitioning = false;

    MenuState currentMenuState = MenuState::MAIN;
    MenuState nextMenuState = MenuState::MAIN;

public:
    virtual void levelLoad();
    virtual void levelInit();
    virtual void levelUpdate();
    virtual void levelDraw();
    virtual void levelFree();
    virtual void levelUnload();

    virtual void isReceivingNoInputs();

    virtual void handleKey(char key);
    virtual void handleMouse(int type, int x, int y);
    virtual void handleControllerButton(SDL_GameControllerButton button);
    virtual void handleAnalogStick(int type, char key);

    virtual void updateObjects(list<DrawableObject*>& objectsList);
    virtual void addObject(DrawableObject* obj);
    
    virtual void renderGUI();

    virtual void changeMenuState(MenuState targetState);
    virtual MenuState getMenuState() const;
};
