#pragma once
#include "BossStateM.h"
#include "Ziz.h"
#include "Level.h"
#include "EnemyAttackCollider.h"

class Ziz;

class ZizClawSlashState : public BossStateM {
private:
    static ZizClawSlashState* instance;

    int facingDirection; //-1 for facing left, 1 for facing right

    int slashCount;
    bool isSlashing;
    bool hasSlashed;
    bool isPreparing;
    bool isStartingUp;

    float attackOffSet;

    float startUpTimer;

    float startUpTimer1;
    float activeTimer1;
    float pauseTimer1;

    float startUpTimer2;
    float activeTimer2;
    float pauseTimer2;

    float startUpTimer3;
    float activeTimer3;
    float pauseTimer3;

    float recoveryTimer;
    float mapXLimit;


    Ziz* ziz;
    Player* player;
    EnemyAttackCollider* attackCollider1; //slash 1
    EnemyAttackCollider* attackCollider2; //slash 2
    EnemyAttackCollider* attackCollider3; //slash 3

public:

    static ZizClawSlashState* getInstance();

    void enter(Boss* boss) override;
    void update(Boss* boss, float dt) override;
    void exit(Boss* boss) override;
    void findPlayer();

};