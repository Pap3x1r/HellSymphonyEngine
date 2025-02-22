#pragma once
#include "TexturedObject.h"
#include "Health.h"
#include "StateMachine.h"

//Movesets
#include "PlayerMovementState.h"
#include "PlayerBowState.h"
#include "PlayerSwordState.h"
#include "PlayerShieldState.h"

class Bow;
class Sword;
class Shield;
class Level;

enum WeaponType {
    None_,
    Sword_,
    Bow_,
    Shield_
};

class Player : public TexturedObject {
    float movementSpeed = 10.0f;
    float jumpingPower = 16.0f;

    bool isFacingRight = true;
    bool isGrounded = true;
    
    WeaponType currentWeapon = WeaponType::None_;

    float ultimateGaugeMax = 100.0f;
    float currentUltimateGauge = 0.0f; //For ultimate attack
    int ultimateSlotMax = 5;
    int currentUltimateSlot = 0;

    bool canMove = true;

    Level* currentLevel;
    Health* health;
    StateMachine* playerState;

    Bow* bow;
    Sword* sword;
    Shield* shield;

public:
    Player(float hp);
    ~Player();

    void selfUpdate(float dt_) {
        if (currentUltimateGauge >= ultimateGaugeMax) {
            increaseUltimateGauge(1);
            currentUltimateGauge -= ultimateGaugeMax;
        }
    }

    void increaseUltimateGauge(float amount) {
        currentUltimateGauge += amount;
    }
    void setUltimateGauge(float amount) {
        currentUltimateGauge = amount;
    }
    bool getUltimateGauge() const {
        return currentUltimateGauge;
    }

    void increaseUltimateSlot(int amount) {
        currentUltimateSlot += amount;
    }
    void setUltimateSlot(int amount) {
        currentUltimateSlot = amount;
    }
    bool getUltimateSlot() const {
        return currentUltimateSlot;
    }


    void setFacingRight(bool value);
    bool getFacingRight() const;

    void setMovementSpeed(float value);
    float getMovementSpeed() const;

    StateMachine* getStateMachine() const;

    void setWeaponType(WeaponType newType);
    WeaponType getWeaponType() const;

    void setLevel(Level* newLevel);
    Level* getLevel() const;

    Bow* getBow() const;
    Sword* getSword() const;
    Shield* getShield() const;

    void onTriggerEnter(Collider* collider) override;
};