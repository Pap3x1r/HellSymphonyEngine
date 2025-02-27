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
    float movementSpeed = 5.0f;
    float jumpingPower = 0.5f;

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

    vector<string> texturePaths;

public:
    Player(float hp);
    ~Player();

    void selfUpdate(float dt_) {

        static float time;
        time += dt_;

        if (currentUltimateSlot < ultimateSlotMax) {
            if (currentUltimateGauge >= ultimateGaugeMax) {
                increaseUltimateSlot(1);
                currentUltimateGauge -= ultimateGaugeMax;
                cout << "Ultimate Slot is increased by 1, the current is: " << currentUltimateSlot << endl;
            }
        }
        else {
            //cout << "Ultimate Slot is maxed" << endl;
            if (currentUltimateGauge > 0.0f) {
                setUltimateGauge(0.0f); //Prevent excess gauge when ultimate slot is maxed
            }
        }
        
        //cout << "Player position x: " << getTransform().getPosition().x << " y: " << getTransform().getPosition().y << endl;

        if (time >= 1.50f) {
            time = 0.0f;
            cout << "Current Ultimate Gauge: " << currentUltimateGauge << endl;
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

    void setJumpPower(float value);
    float getJumpPower() const;

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