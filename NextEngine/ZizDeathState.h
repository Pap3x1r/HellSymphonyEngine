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

class Ziz;


class ZizDeathState : public BossStateM {
private:

    static ZizDeathState* instance;
    float deathTimer;

    Ziz* ziz;
    Player* player;

public:
    static ZizDeathState* getInstance();

    void enter(Boss* boss) override;
    void update(Boss* boss, float dt) override;
    void exit(Boss* boss) override;

};