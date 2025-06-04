#pragma once
#include "BossStateM.h"
#include "Lucifer.h"
#include "Player.h"
#include "LuciferIdleState.h"
#include "Level.h"

class Lucifer;

class LuciferFreeHitState : public BossStateM {
private:

    static LuciferFreeHitState* instance;
    float idleTimer;

    Lucifer* lucifer;

public:
    static LuciferFreeHitState* getInstance();

    void enter(Boss* boss) override;
    void update(Boss* boss, float dt) override;
    void exit(Boss* boss) override;

};