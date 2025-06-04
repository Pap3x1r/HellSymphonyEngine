#pragma once
#include "BossStateM.h"
#include "Lucifer.h"
#include "Player.h"
#include "LuciferHeartBeat.h"
#include "LuciferVerticalBarrageState.h"
#include "LuciferHorizontalBarrageState.h"
#include "LuciferHomingSpearState.h"
#include "LuciferIceBombState.h"
#include "LuciferVerticalBeamState.h"
#include "LuciferBeamRadiantState.h"
#include "LuciferQTEState.h"
#include "LuciferIceFloorState.h"
#include "Level.h"

class Lucifer;

class LuciferIdleState : public BossStateM {
private:

    static LuciferIdleState* instance;
    float idleTimer;

    Lucifer* lucifer;
    Player* player;
    LuciferHeartBeat* luciferHeartBeat;

public:
    static LuciferIdleState* getInstance();

    void enter(Boss* boss) override;
    void update(Boss* boss, float dt) override;
    void exit(Boss* boss) override;
    void pickState();

};