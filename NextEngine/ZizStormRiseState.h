#pragma once
#include "BossStateM.h"
#include "Ziz.h"
#include "Gust.h"
#include "Level.h"

class Ziz;


class ZizStormRiseState : public BossStateM {
private:
    static ZizStormRiseState* instance;
    float startupTimer;
    float recoveryTimer;

public:

    static ZizStormRiseState* getInstance();

    void enter(Boss* boss) override;
    void update(Boss* boss, float dt) override;
    void exit(Boss* boss) override;

};