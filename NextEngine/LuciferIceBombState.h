#pragma once
#include "BossStateM.h"
#include "Lucifer.h"
#include "Player.h"
#include "LuciferHeartBeat.h"
#include "IceBomb.h"
#include <algorithm>
#include <random>

class Lucifer;

class LuciferIceBombState : public BossStateM {
private:

    static LuciferIceBombState* instance;

    std::vector<float> slotPositions;
    int nextBombIndex = 0;
    float spawnTimer = 0.0f;
    float delayBetweenBombs = 0.4f;
    float totalDuration = 4.0f;

    Lucifer* lucifer;
    float timer;



public:
    static LuciferIceBombState* getInstance();

    void enter(Boss* boss) override;
    void update(Boss* boss, float dt) override;
    void exit(Boss* boss) override;

};