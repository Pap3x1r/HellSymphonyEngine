#pragma once

#include "BossStateM.h"
#include "Ziz.h"
#include "Level.h"
#include "Player.h"
#include "EnemyAttackCollider.h"

class Ziz;

class ZizGroundSlamState : public BossStateM {
private:
    static ZizGroundSlamState* instance;

    Ziz* ziz = nullptr;
    Player* player = nullptr;
    EnemyAttackCollider* attackCollider = nullptr;

    // Phase control
    bool hasLaunched = false;
    bool peakReached = false;
    bool isDescending = false;
    bool hasImpacted = false;
    bool tooClose = false;
    bool wayTooClose = false;
    bool hasStartUp = false;

    // Timers
    float startupTime;
    float flyupTime;
    float hoverTime;
    float slamTimer;
    float descendTime = 0.0f;
    float recoverTime = 0.0f;

    // Movement points
    glm::vec3 startupPosition;
    glm::vec3 midairTarget;
    glm::vec3 slamStartPos;
    glm::vec3 impactPosition;
    void selectTarget();

public:
    static ZizGroundSlamState* getInstance();

    void enter(Boss* boss) override;
    void update(Boss* boss, float dt) override;
    void exit(Boss* boss) override;
};
