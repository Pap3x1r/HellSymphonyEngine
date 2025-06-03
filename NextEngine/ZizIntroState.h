#pragma once
#include "BossStateM.h"
#include "Ziz.h"
#include "Player.h"


class Ziz;


class ZizIntroState : public BossStateM {
private:

    static ZizIntroState* instance;
    float timer;

    Ziz* ziz;

public:
    static ZizIntroState* getInstance();

    void enter(Boss* boss) override;
    void update(Boss* boss, float dt) override;
    void exit(Boss* boss) override;

};