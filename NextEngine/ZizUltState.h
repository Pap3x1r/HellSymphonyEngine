#pragma once
#include "BossStateM.h"
#include "Ziz.h"
#include "Level.h"
#include "EnemyAttackCollider.h"
#include "DrawableObject.h"
#include "Lightning.h"

class Ziz;

class ZizUltState : public BossStateM {
private:
    static ZizUltState* instance;

    bool hasFlew;
    bool isOffScreen;

    DrawableObject* ultZizOnBG;

    float flyUpTimer;
    float activeLightning;

    Ziz* ziz;


public:

    static ZizUltState* getInstance();

    void enter(Boss* boss) override;
    void update(Boss* boss, float dt) override;
    void exit(Boss* boss) override;

};
