#pragma once
#include <SDL.h>
#include <iostream>

class FrameRateCounter {
private:
    Uint32 lastTime = 0;  // Time at the last frame
    Uint32 currentTime = 0;  // Time at the current frame
    int frameCount = 0;  // Number of frames rendered
    float fps = 0.0f;  // Current FPS value

public:
    void update() {
        currentTime = SDL_GetTicks();  // Get current time in milliseconds
        frameCount++;

        // If a second has passed, update the FPS and reset the frame count
        if (currentTime - lastTime >= 1000) {
            fps = frameCount;  // FPS is the number of frames per second
            frameCount = 0;  // Reset frame count for next second
            lastTime = currentTime;  // Update the last time
        }
    }

    void displayFPS() {
        std::cout << "FPS: " << fps << std::endl;  // Print FPS
    }
};