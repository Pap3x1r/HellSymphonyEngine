#pragma once
#include "BossStateM.h"
#include "Lucifer.h"
#include "Player.h"

class Lucifer;

class LuciferIdleState : public BossStateM {
private:

    static LuciferIdleState* instance;
    float idleTimer;

    Lucifer* lucifer;
    Player* player;

public:
    static LuciferIdleState* getInstance();

    void enter(Boss* boss) override;
    void update(Boss* boss, float dt) override;
    void exit(Boss* boss) override;
    void pickState();

};