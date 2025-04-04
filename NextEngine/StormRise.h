#pragma once
#include "DrawableObject.h"
#include "Boss.h"
#include "Player.h"
#include "Ziz.h"
#include "EnemyAttackCollider.h"
#include "Shield.h"


class StormRise : public EnemyAttackCollider {
private:
    bool playerIsInside;
    bool hasHit;
    bool isActive;
    bool isBuffering;
    bool isRecovering;
    bool canAnim;
    float speed;
    float damage;
    float countdownTimer;
    float activeTimer;
    float recoveryTimer;
    float bufferTimer;
    Player* player;

public:
    
    StormRise();
    void update(float dt);
    void onCollisionEnter(Collider* collider) override;
    void onCollisionStay(Collider* collider) override;
    void onCollisionExit(Collider* collider) override;
    void onTriggerEnter(Collider* collider) override;
    void onTriggerStay(Collider* collider) override;
    void onTriggerExit(Collider* collider) override;
    void setPlayer(Player* playr);
    bool getCanAnim();
    void setAnimStorm();
};
