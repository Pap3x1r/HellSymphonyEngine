#pragma once
#include "BossStateM.h"
#include "Lucifer.h"
#include "Player.h"
#include "LuciferHeartBeat.h"
#include "IceSpear.h"
#include <algorithm>
#include <random>

class Lucifer;

class LuciferHorizontalBarrageState : public BossStateM {
private:

    static LuciferHorizontalBarrageState* instance;

    Lucifer* lucifer;
    float timer;


public:
    static LuciferHorizontalBarrageState* getInstance();

    void enter(Boss* boss) override;
    void update(Boss* boss, float dt) override;
    void exit(Boss* boss) override;

};