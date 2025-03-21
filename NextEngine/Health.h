#pragma once
#include "GameEngine.h"

class Health {
    float realHealth;
    float currentHealth;
    float maxHealth;
    float witherHealth;
    float witherRecoverRate;
    float witherDecreasePercent;

    bool destroyOnDead;

public:
    Health(float health, float wither)
    {
        realHealth = currentHealth = maxHealth = health;
        witherHealth = wither;
    }

    Health(float health) {
        realHealth = currentHealth = maxHealth = health;
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

        if (currentHealth + witherHealth > maxHealth)
        {
            currentHealth = maxHealth;
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
        if (witherHealth > 0)
        {
            witherHealth -= amount * (witherDecreasePercent / 100.0f);
        }

        currentHealth -= amount;
    }
    
    void takeDamage(float amount, float witherPercent)
    {
        if (witherHealth > 0)
        {
            witherHealth -= amount * (witherDecreasePercent / 100.0f);
        }

        witherHealth += amount * (witherPercent / 100.0f);

        currentHealth -= amount * ((100.0f - witherPercent) / 100.0f);
    }

    void heal(float amount)
    {
        if (witherHealth > 0)
        {
            if (amount > witherHealth)
            {
                amount -= witherHealth;
                witherHealth = 0;
            }
            else
            {
                witherHealth -= amount;
                amount = 0;
            }
        }

        if (currentHealth + amount > maxHealth)
        {
            currentHealth = maxHealth;
        }
        else
        {
            currentHealth += amount;
        }
    }

    void healWither(float amount)
    {
        if (witherHealth - amount < 0)
        {
            witherHealth = 0;
        }
        else
        {
            witherHealth -= amount;
        }
    }

    float getRealHP() { return realHealth; }
    float getCurrentHP() { return currentHealth; }
    float getMaxHP() { return maxHealth; }
    float getWitherHP() { return witherHealth; }
};