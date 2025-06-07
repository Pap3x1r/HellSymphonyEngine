#pragma once
#include "GameEngine.h"

/**
 * @class Health
 * @brief Manages health, wither health, and health-related mechanics such as healing and damage.
 */
class Health {
    float realHealth;             ///< Real health = current - wither.
    float currentHealth;          ///< Current visible health.
    float maxHealth = 100.0f;     ///< Maximum health capacity.
    float witherHealth;           ///< Wither health, representing delayed or persistent damage.
    float witherRecoverRate;     ///< Rate at which wither health recovers.
    float witherDecreasePercent = 0.0f; ///< Percentage of damage that affects wither health.

    bool destroyOnDead;          ///< Whether to destroy the object on death.

public:
    /**
     * @brief Full constructor with health, wither health, and max health.
     */
    Health(float health, float wither, float maxHealth_)
    {   
        maxHealth = maxHealth_;
        realHealth = currentHealth = health;
        witherHealth = wither;
    }
    /**
     * @brief Constructor with health and wither health.
     */
    Health(float health, float wither)
    {
        realHealth = currentHealth = health;
        witherHealth = wither;
    }
    /**
     * @brief Constructor with only current health.
     */
    Health(float health) {
        realHealth = currentHealth = health;
        witherHealth = 0;
    }

    /**
     * @brief Updates health status, handles recovery and health limits.
     */
    void healthUpdate()
    {
        bool recovering = false;
        realHealth = currentHealth - witherHealth;

        if (witherHealth > 0)
        {
            recovering = true;
        }

        if (witherHealth < 0)
        {
            witherHealth = 0;
        }


        if (currentHealth > maxHealth) {
            currentHealth = maxHealth;
        }

        if (currentHealth + witherHealth > maxHealth) //Adjust wither health if currentHealth exceeds max
        {
            witherHealth = maxHealth - currentHealth;
        }

        if (recovering)
        {
            witherHealth -= witherRecoverRate * GameEngine::getInstance()->getTime()->getDeltaTime();
            if (witherHealth <= 0)
            {
                witherHealth = 0;
                recovering = false;
            }
        }

        checkHP();
    }

    /**
     * @brief Checks current health and handles death logic.
     * @return Current health.
     */
    float checkHP()
    {
        if (realHealth <= 0)
        {
            currentHealth = 0;
            if (destroyOnDead)
            {
                //Destroy object
            }
        }

        return currentHealth;
    }

    /// Sets current health directly.
    void setHP(float value)
    {
        currentHealth = value;
    }

    /// Sets wither health directly.
    void setWitherHP(float value) {
        witherHealth = value;
    }

    /**
     * @brief Applies damage and decreases wither health based on configured percentage.
     * @param amount Amount of damage.
     */
    void takeDamage(float amount)
    {
        float decreaseAmount = amount * (witherDecreasePercent / 100.0f);

        if (decreaseAmount > witherHealth) {
            witherHealth = 0;  // Prevent negative wither health
        }
        else {
            witherHealth -= decreaseAmount;
        }

        currentHealth -= amount;

        if (currentHealth < 0) {
            currentHealth = 0;
        }

        // Prevent total health (current + wither) exceeds maxHealth
        if (currentHealth + witherHealth > maxHealth) {
            witherHealth = maxHealth - currentHealth;
        }
    }
    
    /**
     * @brief Applies damage and adds wither damage based on wither percentage.
     * @param amount Amount of damage.
     * @param witherPercent Percent of damage converted to wither.
     */
    void takeDamage(float amount, float witherPercent)
    {   

        float decreaseAmount = amount * (witherDecreasePercent / 100.0f);

        if (decreaseAmount > witherHealth) {
            witherHealth = 0;  // Prevent negative wither health
        }
        else {
            witherHealth -= decreaseAmount;
        }

        // Convert part of damage into wither health
        float witherGain = amount * (witherPercent / 100.0f);
        witherHealth += witherGain;

        // Take full damage to real health
        currentHealth -= amount;

        // Prevent negative health
        if (currentHealth < 0) {
            currentHealth = 0;
        }

        if (currentHealth + witherHealth > maxHealth) {
            witherHealth = maxHealth - currentHealth;
        }
    }

    /**
     * @brief Heals current health and optionally reduces wither health.
     * @param amount Amount to heal.
     */
    void heal(float amount)
    {   
        if (currentHealth + amount > maxHealth)
        {
            currentHealth = maxHealth;
        }
        else
        {
            currentHealth += amount;
        }

        if (witherHealth > 0)
        {
            if (amount >= witherHealth)
            {
                witherHealth = 0.0f;
            }
            else
            {
                witherHealth -= amount;
            }
        }
    }

    /**
     * @brief Heals only wither health by converting it back to regular health.
     * @param amount Amount to heal.
     */
    void healWither(float amount)
    {
        if (witherHealth > 0)
        {
            float drained = 0.0f;

            if (amount > witherHealth)
            {
                drained = witherHealth;
                witherHealth = 0.0f;
            }
            else
            {
                drained = amount;
                witherHealth -= amount;
            }

            if (currentHealth + drained > maxHealth)
            {
                currentHealth = maxHealth;
            }
            else
            {
                currentHealth += drained;
            }
        }
    }

    /// Returns real health (current - wither).
    float getRealHP() { return realHealth; }
    /// Returns current visible health.
    float getCurrentHP() { return currentHealth; }
    /// Returns pointer to current health (useful for ImGui binding).
    float* getCurrentHPAddress() { return &currentHealth; }
    /// Returns max health.
    float getMaxHP() { return maxHealth; }
    /// Returns wither health.
    float getWitherHP() { return witherHealth; }
};