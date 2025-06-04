#pragma once
#include "BossStateM.h"
#include "Lucifer.h"
#include "Player.h"
#include "LuciferHeartBeat.h"
#include "IceSpear.h"
#include <algorithm>
#include <random>

class Lucifer;

class LuciferHomingSpearState : public BossStateM {
private:

    static LuciferHomingSpearState* instance;

    Lucifer* lucifer;
    float timer;

    std::vector<float> slotPositions;
    int nextSpearIndex = 0;
    float spawnTimer = 0.0f;
    float delayBetweenSpears = 0.4f;
    float totalDuration = 4.0f;


public:
    static LuciferHomingSpearState* getInstance();

    void enter(Boss* boss) override;
    void update(Boss* boss, float dt) override;
    void exit(Boss* boss) override;

};