#pragma once
#include "BossStateM.h"
#include "Lucifer.h"
#include "Player.h"
#include "LuciferHeartBeat.h"
#include "SideStaff.h"
#include <algorithm>
#include <random>

class Lucifer;

class LuciferSideLaserState : public BossStateM {
private:

    static LuciferSideLaserState* instance;

    Lucifer* lucifer;
    float timer;



public:
    static LuciferSideLaserState* getInstance();

    void enter(Boss* boss) override;
    void update(Boss* boss, float dt) override;
    void exit(Boss* boss) override;

};