#pragma once
#include "GameEngine.h"

class Health {
    float realHealth;
    float currentHealth;
    float maxHealth = 100.0f;
    float witherHealth;
    float witherRecoverRate;
    float witherDecreasePercent = 0.0f;

    bool destroyOnDead;

public:

    Health(float health, float wither, float maxHealth_)
    {   
        maxHealth = maxHealth_;
        realHealth = currentHealth = health;
        witherHealth = wither;
    }

    Health(float health, float wither)
    {
        realHealth = currentHealth = health;
        witherHealth = wither;
    }

    Health(float health) {
        realHealth = currentHealth = health;
        witherHealth = 0;
    }

    // Update is called once per frame

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

    void setHP(float value)
    {
        currentHealth = value;
    }

    void setWitherHP(float value) {
        witherHealth = value;
    }

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

    float getRealHP() { return realHealth; }
    float getCurrentHP() { return currentHealth; }
    float* getCurrentHPAddress() { return &currentHealth; }
    float getMaxHP() { return maxHealth; }
    float getWitherHP() { return witherHealth; }
};