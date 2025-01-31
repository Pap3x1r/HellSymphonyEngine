#pragma once
#include "TexturedObject.h"
#include "Health.h"

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

    Health* health;

public:
    Player(float hp);
    ~Player();

    void setFacingRight(bool value);
    bool getFacingRight() const;

    void setMovementSpeed(float value);
    float getMovementSpeed() const;
};