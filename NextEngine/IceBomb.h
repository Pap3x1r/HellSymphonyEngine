#pragma once
#include "DrawableObject.h"
#include "Boss.h"
#include "Player.h"
#include "Lucifer.h"
#include "EnemyAttackCollider.h"
#include "Shield.h"

class IceBomb : public EnemyAttackCollider {
private:

    float duration;
    bool hasHit;
    float damage;


    bool hasStarted;
    bool hasBombed;

    bool isActive;

    float startUpTimer;
    float activeTimer;
    float recoveryTimer;

public:
    IceBomb();
    IceBomb(float pos);
    void update(float dt);
    void checkOffMap();
    void onCollisionEnter(Collider* collider) override;
    void onCollisionStay(Collider* collider) override;
    void onCollisionExit(Collider* collider) override;
    void onTriggerEnter(Collider* collider) override;
    void onTriggerStay(Collider* collider) override;
    void onTriggerExit(Collider* collider) override;
};
