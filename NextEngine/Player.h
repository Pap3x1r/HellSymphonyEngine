#pragma once
#include "TexturedObject.h"
#include "GroundChecker.h"
#include "Health.h"
#include "StateMachine.h"
#include <imgui.h>
#include <random>
#include "WeaponType.h"

//Movesets
#include "PlayerMovementState.h"
#include "PlayerBowState.h"
#include "PlayerSwordState.h"
#include "PlayerShieldState.h"

class Bow;
class Sword;
class Shield;
class Level;

class Player : public TexturedObject {
    int playerLives = 3;
    bool isDead = false;
    bool isStunned = false;

    float stunTimer = 0.0f;
    float movementSpeed = 5.0f;
    float minMovementSpeed = 5.0f;
    float maxMovementSpeed = 20.0f;
    float jumpingPower = 1.0f;

    bool isFacingRight = true;
    bool isGrounded = false;
    
    bool isInvincible = false;
    float invincibleTimer = 0.0f;

    WeaponType currentWeapon = WeaponType::None_;

    float ultimateGaugeMax = 100.0f;
    float currentUltimateGauge = 0.0f; //For ultimate attack
    int ultimateSlotMax = 5;
    int currentUltimateSlot = 0;

    bool canMove = true;

    bool canDash = true;
    bool isDashing = true;
    float dashCooldown = 1.0f;
    float dashTimer = 0.0f;

    //cam
    bool isShaking = false;
    float shakeDuration = 0.0f;
    float shakeTimer = 0.0f;
    float shakeIntensity = 15.0f; // Adjust for desired intensity
    bool shakeInterval;
    bool shakeIntervalTimer;
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<> shakeOffsetX;
    std::uniform_real_distribution<> shakeOffsetY;

    Level* currentLevel;
    Health* health;
    StateMachine* playerState;

    Bow* bow;
    Sword* sword;
    Shield* shield;
    
    GroundChecker* groundChecker;

    vector<string> texturePaths;

    float velocityThreshold = 0.02f;

public:
    Player(float currentHealth, float witherHealth, int life);
    ~Player();

    void selfUpdate(float dt_);

    void setLives(int value) {
        playerLives = value;
    }

    void setIsDead(bool value) {
        isDead = value;
    }

    bool getIsDead() const {
        return isDead;
    }

    int getLives() const {
        return playerLives;
    }

    void setInvincibleBool(bool value) {
        isInvincible = value;
    }

    void setInvincibleFloat(float value) {
        isInvincible = true;
        invincibleTimer = value;
    }

    bool getInvincible() const {
        return isInvincible;
    }

    void setCanDash(bool value) {
        canDash = value;
    }
    bool getCanDash() const {
        return canDash;
    }

    void setIsDashing(bool value) {
        isDashing = value;
    }
    bool getIsDashing() const {
        return isDashing;
    }

    bool getIsStunned() const {
        return isStunned;
    }

    void increaseUltimateGauge(float amount) {
        currentUltimateGauge += amount;
    }
    void setUltimateGauge(float amount) {
        currentUltimateGauge = amount;
    }
    float getUltimateGauge() const {
        return currentUltimateGauge;
    }

    void increaseUltimateSlot(int amount) {
        currentUltimateSlot += amount;
    }
    void setUltimateSlot(int amount) {
        currentUltimateSlot = amount;
    }
    int getUltimateSlot() const {
        return currentUltimateSlot;
    }
    int getUltimateSlotMax() const {
        return ultimateSlotMax;
    }

    void setIsGrounded(bool value) {
        isGrounded = value;
    }
    bool getIsGrounded() const {
        return isGrounded;
    }

    void setFacingRight(bool value);
    bool getFacingRight() const;

    void setMovementSpeed(float value);
    float getMovementSpeed() const;

    void setJumpPower(float value);
    float getJumpPower() const;

    StateMachine* getStateMachine() const;

    GroundChecker* getGroundChecker() const;

    void setWeaponType(WeaponType newType);
    WeaponType getWeaponType() const;

    void setLevel(Level* newLevel);
    Level* getLevel() const;

    Health* getHealth() const;

    Bow* getBow() const;
    Sword* getSword() const;
    Shield* getShield() const;

    void startShake(float duration, float intensity);
    void updateShake(float deltaTime);
    void stopShake();

    void stun(float duration);

    /*void onCollisionEnter(Collider* collider) override;
    void onCollisionStay(Collider* collider) override;

    void onTriggerEnter(Collider* collider) override;
    void onTriggerStay(Collider* collider) override;*/
};