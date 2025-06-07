#pragma once

#include "GameStateList.h"
#include "InputManager.h"
#include <vector>
#include <string>

using namespace std;

class Level;

/**
 * @struct LoadInfo
 * @brief Holds information needed when transitioning to a new level.
 */
struct LoadInfo {
	vector<string> textureDirs;              ///< Directories of textures to load
	GameState nextStateAfterLoad = GameState::GS_MAINMENU; ///< Next state after loading
};

/**
 * @class GameStateController
 * @brief Controls transitions between game states and manages the current level.
 *
 * Responsible for initializing, updating, drawing, and unloading levels, as well
 * as handling user inputs during gameplay.
 */
class GameStateController {
private:
	Level* currentLevel; ///< Pointer to the current level instance

public:
	GameState gameStateCurr; ///< Current game state
	GameState gameStatePrev; ///< Previous game state
	GameState gameStateNext; ///< Next game state to transition to

	LoadInfo pendingLoad; ///< Pending load information for transitioning

	/**
	 * @brief Constructor for GameStateController.
	 */
	GameStateController();

	/**
	 * @brief Initializes the game state controller with a starting state.
	 * @param gameStateInit Initial game state.
	 */
	void init(GameState gameStateInit);

	/**
	 * @brief Loads the current level resources.
	 */
	void loadLevel();

	/**
	 * @brief Initializes the level logic and assets.
	 */
	void initLevel();

	/**
	 * @brief Updates the level logic.
	 */
	void updateLevel();

	/**
	 * @brief Draws the level visuals.
	 */
	void drawLevel();

	/**
	 * @brief Frees level resources without unloading.
	 */
	void freelevel();

	/**
	 * @brief Unloads the level and cleans up.
	 */
	void unloadLevel();

	/**
	 * @brief Handles keyboard input for the current level.
	 * @param key The pressed key.
	 */
	void handleKeyLevel(char key);

	/**
	 * @brief Handles controller button input for the current level.
	 * @param button SDL game controller button.
	 */
	void handleControllerButtonLevel(SDL_GameControllerButton button);

	/**
	 * @brief Handles mouse input for the current level.
	 * @param type The type of mouse event.
	 * @param x X position of the mouse.
	 * @param y Y position of the mouse.
	 */

	void handleMouseLevel(int type, int x, int y);

	/**
	 * @brief Handles analog stick or trigger input.
	 * @param type Input type.
	 * @param key Identifier for the analog input.
	 */
	void handleAnalogLevel(int type, char key);

	/**
	 * @brief Called when inputs should not be processed.
	 */
	void handleNotReceivingInputs();

	/**
	 * @brief Gets a pointer to the current level.
	 * @return Pointer to the Level object.
	 */
	Level* getLevel() const {
		return currentLevel;
	}
};