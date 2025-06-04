#pragma once
#include "BossStateM.h"
#include "Lucifer.h"
#include "Player.h"
#include "LuciferHeartBeat.h"
#include "VerticalIceBeam.h"
#include <algorithm>
#include <random>

class Lucifer;

class LuciferVerticalBeamState : public BossStateM {
private:

    static LuciferVerticalBeamState* instance;

    Lucifer* lucifer;
    float timer;



public:
    static LuciferVerticalBeamState* getInstance();

    void enter(Boss* boss) override;
    void update(Boss* boss, float dt) override;
    void exit(Boss* boss) override;

};