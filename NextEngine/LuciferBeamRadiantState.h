#pragma once
#include "BossStateM.h"
#include "Lucifer.h"
#include "Player.h"
#include "LuciferHeartBeat.h"
#include "BeamRadiant.h"
#include <algorithm>
#include <random>

class Lucifer;

class LuciferBeamRadiantState : public BossStateM {
private:

    static LuciferBeamRadiantState* instance;

    Lucifer* lucifer;
    float timer;



public:
    static LuciferBeamRadiantState* getInstance();

    void enter(Boss* boss) override;
    void update(Boss* boss, float dt) override;
    void exit(Boss* boss) override;

};