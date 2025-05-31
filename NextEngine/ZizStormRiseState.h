#pragma once
#include "BossStateM.h"
#include "Ziz.h"
#include "Gust.h"
#include "Level.h"

class Ziz;


class ZizStormRiseState : public BossStateM {
private:
    static ZizStormRiseState* instance;
    float startupTimer1;
    float startupTimer2;
    float activeTimer;
    float recoveryTimer1;
    float recoveryTimer2;
    float recoveryTimer3;
    int state;

public:

    static ZizStormRiseState* getInstance();

    void enter(Boss* boss) override;
    void update(Boss* boss, float dt) override;
    void exit(Boss* boss) override;

};