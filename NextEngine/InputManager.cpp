#include "InputManager.h"
#include "GameEngine.h"


InputManager::InputManager() : mouseX(0), mouseY(0), controller(nullptr), leftTrigger(0.0f), rightTrigger(0.0f) {
    // Initialize SDL controller subsystem
    SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER);
    if (SDL_NumJoysticks() > 0) {
        controller = SDL_GameControllerOpen(0); // Open the first controller
    }
}

InputManager::~InputManager() {
    if (controller) {
        SDL_GameControllerClose(controller);
    }
}

void InputManager::updateInput() {
    lastFrameChange = false;
    // Reset key states
    for (auto& pair : keyStates) {
        auto& key = pair.first;
        auto& state = pair.second;
        if (state == KEY_PRESSED) {
            keyStates[key] = KEY_HELD;
        }
        else if (state == KEY_RELEASED) {
            keyStates[key] = KEY_IDLE;
        }
    }

    // Reset mouse button states
    for (auto& pair : mouseButtonStates) {
        auto& button = pair.first;
        auto& state = pair.second;
        if (state == KEY_PRESSED) {
            mouseButtonStates[button] = KEY_HELD;
        }
        else if (state == KEY_RELEASED) {
            mouseButtonStates[button] = KEY_IDLE;
        }
    }

    // Reset controller button states
    for (auto& pair : buttonStates) {
        auto& button = pair.first;
        auto& state = pair.second;
        if (state == KEY_PRESSED) {
            buttonStates[button] = KEY_HELD;
        }
        else if (state == KEY_RELEASED) {
            buttonStates[button] = KEY_IDLE;
        }
    }

    // Poll events
    SDL_Event event;
    while (SDL_PollEvent(&event)) {

        if (event.type == SDL_QUIT) {
            GameEngine::getInstance()->getStateController()->gameStateNext = GameState::GS_QUIT;
        }

        // Resizing window
        if (event.type == SDL_WINDOWEVENT) {
            if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                int newWidth = event.window.data1;
                int newHeight = event.window.data2;

                // Update engine dimensions
                GameEngine::getInstance()->setWindowWidth(newWidth);
                GameEngine::getInstance()->setWindowHeight(newHeight);

                // Update OpenGL viewport
                GameEngine::getInstance()->getRenderer()->setViewPort(0, 0, newWidth, newHeight);

                std::cout << "Resized to: " << newWidth << "x" << newHeight << std::endl;
            }
        }

        // Handle keyboard events
        if (event.type == SDL_KEYDOWN && !event.key.repeat) {
            keyStates[event.key.keysym.sym] = KEY_PRESSED;
            setLastInput(InputDevice::KEYBOARD);
        }
        if (event.type == SDL_KEYUP) {
            keyStates[event.key.keysym.sym] = KEY_RELEASED;
            setLastInput(InputDevice::KEYBOARD);
        }

        // Handle mouse events
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            mouseButtonStates[event.button.button] = KEY_PRESSED;
            setLastInput(InputDevice::KEYBOARD);
        }
        if (event.type == SDL_MOUSEBUTTONUP) {
            mouseButtonStates[event.button.button] = KEY_RELEASED;
            setLastInput(InputDevice::KEYBOARD);
        }

        // Handle controller events
        if (event.type == SDL_CONTROLLERBUTTONDOWN) {
            buttonStates[event.cbutton.button] = KEY_PRESSED;
            setLastInput(InputDevice::CONTROLLER);
        }
        if (event.type == SDL_CONTROLLERBUTTONUP) {
            buttonStates[event.cbutton.button] = KEY_RELEASED;
            setLastInput(InputDevice::CONTROLLER);
        }

        if (event.type == SDL_CONTROLLERAXISMOTION) {
            const float DEADZONE = 0.2f;
            if (event.caxis.axis == SDL_CONTROLLER_AXIS_LEFTX) {
                analogStick.first = event.caxis.value / 32768.0f; // Capture left stick x-axis
                if (fabs(analogStick.first) > DEADZONE) {
                    setLastInput(InputDevice::CONTROLLER);
                }
            }
            if (event.caxis.axis == SDL_CONTROLLER_AXIS_LEFTY) {
                analogStick.second = event.caxis.value / 32768.0f; // Capture left stick y-axis
                if (fabs(analogStick.second) > DEADZONE) {
                    setLastInput(InputDevice::CONTROLLER);
                }
            }
            if (event.caxis.axis == SDL_CONTROLLER_AXIS_TRIGGERLEFT) {
                // Normalize the trigger value to 0.0f - 1.0f range
                leftTrigger = static_cast<float>(event.caxis.value) / 32767.0f;
                // You might want to clamp the value to ensure it's within the range
                if (leftTrigger < 0.2f) leftTrigger = 0.0f;
                if (leftTrigger > 1.0f) leftTrigger = 1.0f;
                if (leftTrigger > 0.1f) {
                    setLastInput(InputDevice::CONTROLLER);
                }
                // std::cout << "L2 Trigger Value: " << leftTrigger << std::endl; // For debugging
            }
            if (event.caxis.axis == SDL_CONTROLLER_AXIS_TRIGGERRIGHT) {
                // Normalize the trigger value to 0.0f - 1.0f range
                rightTrigger = static_cast<float>(event.caxis.value) / 32767.0f;
                // You might want to clamp the value to ensure it's within the range
                if (rightTrigger < 0.2f) rightTrigger = 0.0f;
                if (rightTrigger > 1.0f) rightTrigger = 1.0f;
                if (rightTrigger > 0.1f) {
                    setLastInput(InputDevice::CONTROLLER);
                }
                // std::cout << "R2 Trigger Value: " << rightTrigger << std::endl; // For debugging
            }
        }

        ImGui_ImplSDL2_ProcessEvent(&event);
    }

    // Update mouse position
    SDL_GetMouseState(&mouseX, &mouseY);

    //std::cout << "Left Stick X: " << analogStick.first << " | Left Stick Y: " << analogStick.second << std::endl;
}

// Key handling methods
bool InputManager::getButtonDown(SDL_Keycode key) {
    return keyStates[key] == KEY_PRESSED;
}

bool InputManager::getButton(SDL_Keycode key) {
    return keyStates[key] == KEY_HELD || keyStates[key] == KEY_PRESSED;
}

bool InputManager::getButtonUp(SDL_Keycode key) {
    return keyStates[key] == KEY_RELEASED;
}

// Mouse handling methods
bool InputManager::getMouseButtonDown(int button) {
    return mouseButtonStates[button] == KEY_PRESSED;
}

bool InputManager::getMouseButton(int button) {
    return mouseButtonStates[button] == KEY_HELD || mouseButtonStates[button] == KEY_PRESSED;
}

bool InputManager::getMouseButtonUp(int button) {
    return mouseButtonStates[button] == KEY_RELEASED;
}

// Controller handling methods
bool InputManager::getControllerButtonDown(Uint8 button) {
    return buttonStates[button] == KEY_PRESSED;
}

bool InputManager::getControllerButton(Uint8 button) {
    return buttonStates[button] == KEY_HELD || buttonStates[button] == KEY_PRESSED;
}

bool InputManager::getControllerButtonUp(Uint8 button) {
    return buttonStates[button] == KEY_RELEASED;
}

float InputManager::getControllerAnalogStickX() {
    return analogStick.first;
}

float InputManager::getControllerAnalogStickY() {
    return analogStick.second;
}

float InputManager::getControllerLeftTrigger(){
    return leftTrigger;
}

float InputManager::getControllerRightTrigger(){
    return rightTrigger;
}


int InputManager::getMouseX() const {
    return mouseX;
}

int InputManager::getMouseY() const {
    return mouseY;
}

bool InputManager::isMovementInputIdle() {
    return !(getButton(SDLK_a) ||
        getButton(SDLK_d) ||
        getButton(SDLK_s) ||
        getControllerButton(SDL_CONTROLLER_BUTTON_DPAD_LEFT) ||
        getControllerButton(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) ||
        getControllerButton(SDL_CONTROLLER_BUTTON_DPAD_UP) ||
        getControllerButton(SDL_CONTROLLER_BUTTON_DPAD_DOWN) ||
        (getControllerAnalogStickX() > 0.15) || (getControllerAnalogStickX() < -0.15)   );
}

void InputManager::setLastInput(InputDevice device) {
    if (!lastFrameChange) {
        if (lastInput != device) {
            lastInput = device;
            switch (device) {
            case InputDevice::KEYBOARD:
                cout << "LastInput: Keyboard\n";
                cout << "Is now: " << to_string(int(device)) << endl;
                break;
            case InputDevice::CONTROLLER:
                cout << "LastInput: Controller\n";
                cout << "Is now: " << to_string(int(device)) << endl;
                break;
            default:
                cout << "LastInput: Unknown\n";
                cout << "Is now: " << to_string(int(device)) << endl;
                break;
            }

         
        }

        lastFrameChange = true;
    }
}

InputDevice InputManager::getLastInput() {
    return lastInput;
}
