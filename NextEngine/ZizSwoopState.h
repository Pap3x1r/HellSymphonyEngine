#pragma once
#include "BossStateM.h"
#include "Ziz.h"
#include "Level.h"
#include "EnemyAttackCollider.h"

class Ziz;


class ZizSwoopState : public BossStateM {
private:
    static ZizSwoopState* instance;

    int swoopDirection; //-1 for left, 1 for right
    bool hasFlew;
    bool isOffScreen;
    bool isDisplayingWarning;
    bool hasDisplayedWarning;
    bool hasReachedTarget;
    
    float flyUpTimer;
    float beforeWarningTimer;
    float warningTimer;
    float swoopTimer;
    float recoveryTimer;
    float beforeSwoopTimer;
    const float swoopDuration = 0.5f;
    float t;
    DrawableObject* newSwoopWarning;

    glm::vec3 endPos;
    glm::vec3 startPos;
    glm::vec3 newPos;

    glm::vec3 endPosUp;
    glm::vec3 startPosUp;
    glm::vec3 newPosUp;


    Ziz* ziz;
    EnemyAttackCollider* attackCollider;

public:

    static ZizSwoopState* getInstance();

    void enter(Boss* boss) override;
    void update(Boss* boss, float dt) override;
    void exit(Boss* boss) override;

};



