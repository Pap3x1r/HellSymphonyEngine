#pragma once
#include "BossStateM.h"
#include "Lucifer.h"
#include "Player.h"
#include "LuciferHeartBeat.h"
#include "IceFloor.h"
#include "IceFloorWarning.h"
#include <algorithm>
#include <random>

class Lucifer;

class LuciferIceFloorState : public BossStateM {
private:

    static LuciferIceFloorState* instance;

    Lucifer* lucifer;

    bool hasSpawnedFloor;
    float spawnFloor;
    float timer;


public:
    static LuciferIceFloorState* getInstance();

    void enter(Boss* boss) override;
    void update(Boss* boss, float dt) override;
    void exit(Boss* boss) override;

};