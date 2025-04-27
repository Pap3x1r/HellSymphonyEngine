#pragma once
#include "BossStateM.h"
#include "Ziz.h"
#include "Level.h"
#include "EnemyAttackCollider.h"
#include "ChompTentacle.h"

class Ziz;

class ZizChompState : public BossStateM {
private:
    static ZizChompState* instance;

    int facingDirection; //-1 for facing left, 1 for facing right

    int chompCount;
    bool isChomping;
    bool hasChomped;
    bool isPreparing;
    bool isStartingUp;
    bool animCorrected;

    float attackOffSet1;
    float attackOffSet2;

    float startUpTimer;

    float startUpTimer1;
    float activeTimer1;
    float pauseTimer1;

    float startUpTimer2;
    float activeTimer2;
    float pauseTimer2;

    float recoveryTimer;
    float animOffsetTimer;


    Ziz* ziz;
    Player* player;
    EnemyAttackCollider* attackCollider1; //chomp 1
    EnemyAttackCollider* attackCollider2; //chomp 2

public:

    static ZizChompState* getInstance();

    void enter(Boss* boss) override;
    void update(Boss* boss, float dt) override;
    void exit(Boss* boss) override;
    void findPlayer();

};