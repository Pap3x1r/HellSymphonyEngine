#pragma once
#include "BossStateM.h"
#include "Ziz.h"
#include "Level.h"
#include "EnemyAttackCollider.h"

class Ziz;

class ZizWingSpanState : public BossStateM {
    private:
        static ZizWingSpanState* instance;
        
        float startupTimer;
        float activeTimer;
        float recoveryTimer;

        bool isCurling;
        bool isAttacking;
        bool hasAttacked;


        Ziz* ziz;
        EnemyAttackCollider* attackCollider;

    public:

        static ZizWingSpanState* getInstance();

        void enter(Boss* boss) override;
        void update(Boss* boss, float dt) override;
        void exit(Boss* boss) override;

};
