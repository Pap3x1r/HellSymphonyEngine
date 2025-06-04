#pragma once
#include "BossStateM.h"
#include "Lucifer.h"
#include "Player.h"
#include "LuciferHeartBeat.h"
#include "IceSpear.h"
#include <algorithm>
#include <random>

class Lucifer;

class LuciferVerticalBarrageState : public BossStateM {
private:

    static LuciferVerticalBarrageState* instance;

    Lucifer* lucifer;
    float timer;


public:
    static LuciferVerticalBarrageState* getInstance();

    void enter(Boss* boss) override;
    void update(Boss* boss, float dt) override;
    void exit(Boss* boss) override;

};