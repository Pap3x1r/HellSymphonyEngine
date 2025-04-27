#pragma once
#include "DrawableObject.h"
#include "Boss.h"
#include "Player.h"
#include "Ziz.h"
#include "EnemyAttackCollider.h"


class ChompTentacle : public TexturedObject {
private:
    bool isFacingRight;
    bool hasHit;
    float damage;
    float chompTimer;

public:
    ChompTentacle();
    ChompTentacle(bool facingRight); //created by ziz
    void update(float dt);
};
