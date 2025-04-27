#pragma once
#include "DrawableObject.h"
#include "Boss.h"
#include "Player.h"
#include "Ziz.h"
#include "EnemyAttackCollider.h"


class ChompTentacle : public TexturedObject {
private:
    bool isFacingRight;
    bool hasAttack1;
    bool hasAttack2;
    float damage;
    float chompTimer;
    float attackOffSet1;
    float attackOffSet2;
    float attackTimer1;
    float attackTimer2;
    float attackduration1;
    float attackduration2;
    Ziz* ziz;


    EnemyAttackCollider* attackCollider1; //chomp 1
    EnemyAttackCollider* attackCollider2; //chomp 2

public:
    ChompTentacle();
    ~ChompTentacle();
    ChompTentacle(bool facingRight,Ziz* boss); //created by ziz
    void update(float dt);
};
