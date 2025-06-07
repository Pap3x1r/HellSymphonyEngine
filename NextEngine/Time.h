#pragma once
#include <SDL.h>

/**
 * @class Time
 * @brief Manages timing and delta time for frame updates and time scaling.
 *
 * Provides time tracking utilities such as delta time (scaled and unscaled),
 * tick counting, and time scale adjustment for use in game loops.
 */
class Time {
private:
    uint64_t tickCounter;   ///< Internal tick counter (in milliseconds or microseconds depending on usage)
    float timeScale;        ///< Time scaling factor (e.g. for slow motion)
    float deltaTime;        ///< Scaled delta time between frames

public:

    /**
     * @brief Constructs a Time object with default values.
     */
    Time();

    /**
     * @brief Gets the time between frames, scaled by timeScale.
     * @return Scaled delta time.
     */
    float getDeltaTime();

    /**
     * @brief Gets the real (unscaled) delta time between frames.
     * @return Raw delta time.
     */
    float getDeltaTimeRealTime();

    /**
     * @brief Gets the current internal tick count.
     * @return Tick counter value.
     */
    uint64_t getTicks();

    /**
     * @brief Updates internal time state and computes delta time.
     * @param time The current tick value.
     */
    void updateTick(uint64_t time);

    /**
     * @brief Updates only the tick counter without computing delta time.
     * @param time The current tick value.
     */
    void updateTickCounterOnly(uint64_t time);

    /**
     * @brief Sets the time scaling factor.
     * @param timeScale The new time scale (e.g. 0.5 for half-speed).
     */
    void setTimeScale(float timeScale);
};