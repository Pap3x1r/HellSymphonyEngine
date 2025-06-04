#pragma once
#include "DrawableObject.h"
#include "Boss.h"
#include "Player.h"
#include "Lucifer.h"
#include "EnemyAttackCollider.h"
#include "Shield.h"


class VerticalIceBeam : public EnemyAttackCollider {
private:

    bool isMovingRight;
    float speed;
    bool hasHit;
    float damage;


    bool hasDelayed;
    float delayBeforeStart;

    float timer;

public:
    VerticalIceBeam();
    VerticalIceBeam(bool facingRight); //created by ziz
    void update(float dt);
    void checkOffMap();
    void onCollisionEnter(Collider* collider) override;
    void onCollisionStay(Collider* collider) override;
    void onCollisionExit(Collider* collider) override;
    void onTriggerEnter(Collider* collider) override;
    void onTriggerStay(Collider* collider) override;
    void onTriggerExit(Collider* collider) override;
};
