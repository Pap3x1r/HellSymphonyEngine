#pragma once
#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <SDL.h>
#include <unordered_map>
#include <iostream>
#include <imgui_impl_sdl2.h>

class GameEngine;

/**
 * @enum InputDevice
 * @brief Enum representing the last input device used.
 */
enum class InputDevice {
    NONE,       ///< No input device detected
    KEYBOARD,   ///< Keyboard input
    MOUSE,      ///< Mouse input
    CONTROLLER  ///< Game controller input
};

/**
 * @class InputManager
 * @brief Manages input from keyboard, mouse, and controllers.
 *
 * Provides functions similar to Unity-style input handling,
 * including polling, state tracking (pressed/held/released),
 * and support for SDL-based input and controllers.
 */
class InputManager {
public:
    /**
     * @enum KeyState
     * @brief Enum for tracking the state of a key or button.
     */
    enum KeyState {
        KEY_IDLE,    // Not pressed
        KEY_PRESSED, // Just pressed this frame
        KEY_HELD,    // Held down across multiple frames
        KEY_RELEASED // Just released this frame
    };

    /**
     * @brief Constructs a new InputManager.
     */
    InputManager();

    /**
     * @brief Destroys the InputManager.
     */
    ~InputManager();

    /**
     * @brief Updates all input states.
     * Should be called once per frame.
     */
    void updateInput();  // Poll inputs and update the state

    /**
     * @brief Checks if a key was just pressed.
     * @param key SDL_Keycode
     * @return True if pressed this frame.
     */
    bool getButtonDown(SDL_Keycode key);      // Equivalent to Input.GetButtonDown

    /**
     * @brief Checks if a key is held down.
     * @param key SDL_Keycode
     * @return True if currently held.
     */
    bool getButton(SDL_Keycode key);          // Equivalent to Input.GetButton

    /**
     * @brief Checks if a key was just released.
     * @param key SDL_Keycode
     * @return True if released this frame.
     */
    bool getButtonUp(SDL_Keycode key);        // Equivalent to Input.GetButtonUp

    /**
     * @brief Checks if a mouse button was just pressed.
     * @param button Mouse button index (e.g. SDL_BUTTON_LEFT)
     * @return True if pressed this frame.
     */
    bool getMouseButtonDown(int button);      // Equivalent to Input.GetMouseButtonDown

    /**
     * @brief Checks if a mouse button is held.
     * @param button Mouse button index
     * @return True if currently held.
     */
    bool getMouseButton(int button);          // Equivalent to Input.GetMouseButton

    /**
     * @brief Checks if a mouse button was just released.
     * @param button Mouse button index
     * @return True if released this frame.
     */
    bool getMouseButtonUp(int button);        // Equivalent to Input.GetMouseButtonUp

    /**
     * @brief Checks if a controller button was just pressed.
     * @param button Controller button ID
     * @return True if pressed this frame.
     */
    bool getControllerButtonDown(Uint8 button); // Equivalent to Input.GetControllerButtonDown

    /**
     * @brief Checks if a controller button is held.
     * @param button Controller button ID
     * @return True if currently held.
     */
    bool getControllerButton(Uint8 button);     // Equivalent to Input.GetControllerButton

    /**
     * @brief Checks if a controller button was just released.
     * @param button Controller button ID
     * @return True if released this frame.
     */
    bool getControllerButtonUp(Uint8 button);   // Equivalent to Input.GetControllerButtonUp


    /**
     * @brief Gets X-axis value of the analog stick.
     * @return Float between -1 and 1.
     */
    float getControllerAnalogStickX();

    /**
     * @brief Gets Y-axis value of the analog stick.
     * @return Float between -1 and 1.
     */
    float getControllerAnalogStickY();

    /**
     * @brief Gets value of the left trigger.
     * @return Float trigger value.
     */
    float getControllerLeftTrigger();
    /**
     * @brief Gets value of the right trigger.
     * @return Float trigger value.
     */
    float getControllerRightTrigger();

    /**
     * @brief Gets current mouse X coordinate.
     * @return X position.
     */
    int getMouseX() const;

    /**
     * @brief Gets current mouse Y coordinate.
     * @return Y position.
     */
    int getMouseY() const;

    /**
     * @brief Checks if any input is currently idle.
     * @return True if no keys/buttons are active.
     */
    bool isMovementInputIdle();                 // Is Receiving Input

    /**
     * @brief Sets the last active input device.
     * @param device Input device type.
     */
    void setLastInput(InputDevice device);

    /**
     * @brief Gets the last active input device.
     * @return Last used InputDevice.
     */
    InputDevice getLastInput();


private:
    std::unordered_map<SDL_Keycode, KeyState> keyStates;   // Map of key states
    std::unordered_map<int, KeyState> mouseButtonStates;   // Mouse button states
    std::unordered_map<Uint8, KeyState> buttonStates;      // Controller button states
    int mouseX, mouseY;                                    // Mouse position
    SDL_GameController* controller;                        // Controller pointer
    std::pair<float, float> analogStick;                   // Analog Stick
    float leftTrigger;
    float rightTrigger;
    
    InputDevice lastInput = InputDevice::CONTROLLER;
    bool lastFrameChange = false;
};

#endif
