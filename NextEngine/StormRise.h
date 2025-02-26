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
    float speed;
    float damage;
    float countdownTimer;
    float activeTimer;
    Player* player;

public:
    StormRise(); //constructor for spawning directly for testing
    StormRise(float cdTimer); //constructor for when ziz summons attack in actual game
    void update(float dt);
    void onCollisionEnter(Collider* collider) override;
    void onCollisionStay(Collider* collider) override;
    void onCollisionExit(Collider* collider) override;
    void onTriggerEnter(Collider* collider) override;
    void onTriggerStay(Collider* collider) override;
    void onTriggerExit(Collider* collider) override;
    void setPlayer(Player* playr);
};
