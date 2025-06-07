#pragma once

#include <vector>
#include "DrawableObject.h"
#include "GLRenderer.h"
#include "GameStateController.h"
#include "Time.h"
#include "InputManager.h" 
#include "SDL_ttf.h"
#include "Audio.h"
#include "WeaponType.h"
#include "SoundManager.h"


/**
 * @file GameEngine.cpp
 * @brief Implements the core game engine including initialization, rendering, saving/loading state and player data.
 *
 * This file contains the singleton implementation of the GameEngine class which handles game initialization,
 * rendering pipeline, game state management, and save/load mechanisms for player and game state data.
 */

class Player;

using namespace std;

class GameEngine {
	static GameEngine* instance;
	int winWidth, winHeight;
	
	GLRenderer *renderer;
	GameStateController* stateController;
	Time* time;
	InputManager* inputHandler;
	vector<string> texturePaths;
	//AudioEngine* audio;

	GameEngine();
public:

	bool isNewGame = false;
	glm::vec3 playerPos = glm::vec3(0.0f);


	/**
	 * Get the GameEngine instance.
	 *
	 * @return GameEngine An instance for GameEngine singleton.
	 */
	static GameEngine* getInstance();

	/**
	 * Get the GLRenderer.
	 *
	 * @return GLRenderer A renderer for rendering game objects.
	 */
	GLRenderer * getRenderer();

	/**
	 * Get the State Controller.
	 *
	 * @return StateController A manager for managing game levels.
	 */
	GameStateController* getStateController();

	/**
	 * Get the Time.
	 *
	 * @return Time A manager for managing in-game time.
	 */
	Time* getTime();
	//AudioEngine* getAudio();

	/**
	 * Get the Input Manager.
	 *
	 * @return InputManager A manager for managing player inputs.
	 */
	InputManager* getInputHandler();// Getter for input handler

	/**
	 * Initialize the game engine and its dependacies.
	 *
	 * @param width The width of the window.
	 * @param height The height of the window.
	 *
	 * @return void
	 */
	void init(int width, int height);

	/**
	 * Set new ortho projection for the renderer.
	 *
	 * @param left The left-most value of the world space.
	 * @param right The right-most value of the world space.
	 * @param bottom The bottom-most value of the world space.
	 * @param top The top-most value of the world space.
	 *
	 * @return void
	 */
	void setDrawArea(float left, float right, float bottom, float top);

	/**
	 * Set new background color for the renderer.
	 *
	 * @param r The red value.
	 * @param g The green value.
	 * @param b the blue value.
	 *
	 * @return void
	 */
	void setBackgroundColor(float r, float g, float b);

	/**
	 * Add a new mesh to the renderer.
	 *
	 * @param name The name of a mesh.
	 * @param mesh The mesh with its attribute.
	 * 
	 * @return void
	 */
	void addMesh(string name, MeshVbo* mesh);

	/**
	 * Clear every meshes from the renderer.
	 *
	 * @return void
	 */
	void clearMesh();

	/**
	 * Send a list of object to the renderer.
	 *
	 * @param renderObjects A list of object that can be rendered.
	 * 
	 * @return void
	 */
	void render(list<DrawableObject*> renderObjects);

	/**
	 * Set new window width.
	 *
	 * @return int The width of window in pixel.
	 */
	int getWindowWidth();

	/**
	 * Set new window width.
	 *
	 * @return int The height of window in pixel.
	 */
	int getWindowHeight();

	/**
	 * Set new window width.
	 *
	 * @param h New width for window in pixel.
	 *
	 * @return void
	 */
	void setWindowWidth(int w);

	/**
	 * Set new window height.
	 *
	 * @param h New height for window in pixel.
	 *
	 * @return void
	 */
	void setWindowHeight(int h);

	/**
	 * Freeze the game for a duration.
	 *
	 * @param duration in seconds.
	 *
	 * @return void
	 */
	void freezeGameForSecond(float duration);

	/**
	 * Saves the player's current health, wither health, and lives to a file.
	 *
	 * @param player The player character.
	 * @param filename The path to the file where data will be saved.
	 *
	 * @return void
	 *
	 * @note This will overwrite the file if it already exists.
	 */
	void savePlayerData(const Player* player, const std::string& filename);

	/**
	 * Saves the player's current health, wither health, and lives to a file.
	 *
	 * @param currentHP The player's current health value.
	 * @param witherHP The player's current wither health.
	 * @param lives Number of lives the player has.
	 * @param filename The path to the file where data will be saved.
	 *
	 * @return void
	 *
	 * @note This will overwrite the file if it already exists.
	 */
	void savePlayerData(int currentHP, int witherHP, int lives, const std::string& filename);

	/**
	 * Load the player's current health, wither health, and lives from a file.
	 *
	 * @param filename The path to the file where data will be loaded.
	 * 
	 * @return Player The player data for load.
	 */
	Player* loadPlayerData(const string& filepath);


	/**
	 * Save the player's game state to a file.
	 *
	 * @param state The current level of the game.
	 * @param filename The path to the file where data will be saved.
	 *
	 * @return void
	 */
	void saveGameState(GameState state, const std::string& filename);

	/**
	 * Load the player's game state from a file.
	 *
	 * @param filename The path to the file where data will be loaded.
	 * @param newGame If true, the game will load to the first level, if not, the game will load from the file.
	 * 
	 * @return GameState The player game state for load.
	 */
	GameState loadGameState(const std::string& filename, bool newGame);

	/**
	 * Save the player's weapon type to a file.
	 *
	 * @param player The data for player.
	 * @param filename The path to the file where data will be saved.
	 *
	 * @return void
	 */
	void savePlayerWeaponType(Player* player, const std::string& filepath);

	/**
	 * Load the player's weapon type from a file.
	 *
	 * @param filename The path to the file where data will be loaded.
	 * @param newGame If true, the game will load player with no weapon, if not, the game will load from the file.
	 *
	 * @return WeaponType The type of weapon player is holding.
	 */
	WeaponType loadPlayerWeaponType(const std::string& filename, bool newGame);
};