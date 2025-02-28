#pragma once
#include "BossStateM.h"
#include "Ziz.h"
#include "Player.h"

class Ziz;


class ZizIdleState : public BossStateM {
private:

    static ZizIdleState* instance;
    float idleTimer = 0.0f;
    float idleWaitTime = 1.0f;

    Ziz* ziz;
    Player* player;

public:
    static ZizIdleState* getInstance();

    void enter(Boss* boss) override;
    void update(Boss* boss, float dt) override;
    void exit(Boss* boss) override;
    void pickState();

};