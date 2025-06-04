#pragma once
#include "DrawableObject.h"
#include "Boss.h"
#include "Player.h"
#include "EnemyAttackCollider.h"
#include "Shield.h"
#include <unordered_set>
#include <cmath>

enum FacingDirection {
    down = 0,
    right,
    left,
    tracking
};

class IceSpear : public EnemyAttackCollider {
private:

    int moveDirection;

    float speed;
    bool hasHit;
    float damage;
    FacingDirection facingDirection;

    bool isInPlace;
    float prepareDuration;
    float prepareTimer;

    bool hasLaunched;
    float delayBeforeLaunch;

    float delayBeforeLaunch2;

    //tracking spear
    bool isTracking = false;
    glm::vec3 trackingDirection;
    Player* targetPlayer = nullptr; 
    glm::vec3 direction;
    float currentAngle = 0.0f;
    float angularVelocity;



    //normal spear
    glm::vec3 startPos;
    glm::vec3 targetPos;
    glm::vec3 newPos;

public:
    IceSpear();
    IceSpear(FacingDirection fd);
    IceSpear(FacingDirection fd, float pos);
    IceSpear(Player* target);
    IceSpear(Player* target, float startPos);
    void update(float dt);
    void checkOffMap();
    void onCollisionEnter(Collider* collider) override;
    void onCollisionStay(Collider* collider) override;
    void onCollisionExit(Collider* collider) override;
    void onTriggerEnter(Collider* collider) override;
    void onTriggerStay(Collider* collider) override;
    void onTriggerExit(Collider* collider) override;
};
