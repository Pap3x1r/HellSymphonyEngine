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

/**
 * @class Level
 * @brief Base class representing a game level with lifecycle and input handling.
 *
 * The Level class manages the core game objects, rendering, input, and transitions.
 */
class Level
{
private:
    list<DrawableObject*> objectsList; ///< List of drawable objects in the level
    Player* player;                    ///< Pointer to the player object
    EnemyObject* enemy;               ///< Pointer to the enemy object
    TexturedObject* background;       ///< Background object

    float transitionTime = 0.0f;      ///< Timer for transitions
    float transitionDuration = 1.0f;  ///< Duration of the transition
    bool transitioning = false;       ///< Flag to indicate if transitioning

    MenuState currentMenuState = MenuState::MAIN; ///< Current menu state
    MenuState nextMenuState = MenuState::MAIN;    ///< Next menu state

public:
    /**
    * @brief Loads all assets and data needed for the level.
    */
    virtual void levelLoad();

    /**
     * @brief Initializes the level (called after load).
     */
    virtual void levelInit();

    /**
     * @brief Updates the level logic.
     */
    virtual void levelUpdate();

    /**
     * @brief Renders all objects in the level.
     */
    virtual void levelDraw();

    /**
     * @brief Frees temporary resources (called before unload).
     */
    virtual void levelFree();

    /**
     * @brief Unloads all resources for the level.
     */
    virtual void levelUnload();

    /**
     * @brief Called when no input is currently being received.
     */
    virtual void isReceivingNoInputs();

    /**
     * @brief Handles keyboard input.
     * @param key The pressed key.
     */
    virtual void handleKey(char key);

    /**
     * @brief Handles mouse input.
     * @param type Mouse event type.
     * @param x X position of the mouse.
     * @param y Y position of the mouse.
     */
    virtual void handleMouse(int type, int x, int y);

    /**
     * @brief Handles controller button input.
     * @param button SDL game controller button.
     */
    virtual void handleControllerButton(SDL_GameControllerButton button);

    /**
     * @brief Handles analog stick input.
     * @param type Analog input type.
     * @param key Identifier for analog input.
     */
    virtual void handleAnalogStick(int type, char key);

    /**
     * @brief Updates all drawable objects in the level.
     * @param objectsList List of drawable objects to update.
     */
    virtual void updateObjects(list<DrawableObject*>& objectsList);

    /**
     * @brief Adds a drawable object to the level.
     * @param obj Pointer to the drawable object.
     */
    virtual void addObject(DrawableObject* obj);
    
    /**
     * @brief Renders GUI elements using ImGui.
     */
    virtual void renderGUI();

    /**
     * @brief Changes the menu state to a new target state.
     * @param targetState The new menu state.
     */
    virtual void changeMenuState(MenuState targetState);

    /**
     * @brief Gets the current menu state.
     * @return The current MenuState.
     */
    virtual MenuState getMenuState() const;
};
