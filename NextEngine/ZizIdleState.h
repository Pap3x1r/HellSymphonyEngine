#pragma once
#include "BossStateM.h"

class Ziz;


class ZizIdleState : public BossStateM {
private:

    static ZizIdleState* instance;
    float idleTimer = 0.0f;
    float idleWaitTime = 3.0f;

public:
    static ZizIdleState* getInstance();

    void enter(Boss* boss) override;
    void update(Boss* boss, float dt) override;
    void exit(Boss* boss) override;

};