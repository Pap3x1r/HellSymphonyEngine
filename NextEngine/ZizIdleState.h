#pragma once
#include "BossStateM.h"
#include "Ziz.h"
#include "Player.h"
#include "ZizGustState.h"
#include "ZizSwoopState.h"
#include "ZizGroundSlamState.h"
#include "ZizWingSpanState.h"
#include "ZizClawSlashState.h"
#include "ZizChompState.h"
#include "ZizUltState.h"
#include "ZizQTEState.h"
#include <random>
#include <chrono>

class Ziz;


class ZizIdleState : public BossStateM {
private:

    static ZizIdleState* instance;
    float idleTimer;

    Ziz* ziz;
    Player* player;

    std::mt19937 gen;
    std::uniform_real_distribution<> randomX;

public:
    static ZizIdleState* getInstance();

    void enter(Boss* boss) override;
    void update(Boss* boss, float dt) override;
    void exit(Boss* boss) override;
    void pickState();

};