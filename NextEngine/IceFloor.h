#pragma once
#include "DrawableObject.h"
#include "Boss.h"
#include "Player.h"
#include "Lucifer.h"
#include "Shield.h"
#include "EnemyAttackCollider.h"

class IceFloor : public TexturedObject {
private:

    float duration;
    bool hasHit;
    float damage;


    bool hasStarted;
    bool hasBombed;

    bool isActive;

    EnemyAttackCollider* atk;

    Lucifer* lucifer;

    float startUpTimer;
    float activeTimer;
    float recoveryTimer;

public:
    IceFloor();
    void update(float dt);

};
