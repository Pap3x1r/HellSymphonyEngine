#pragma once
#include "BossStateM.h"
#include "Ziz.h"
#include "Gust.h"
#include "Level.h"

class Ziz;

class ZizGustState : public BossStateM {
private:
    static ZizGustState* instance;
    float timer;
    float startupTimer;
    float activeTimer;
    float recoveryTimer;
    int currentState;

    Ziz* ziz;

public:
    
    static ZizGustState* getInstance();

    void enter(Boss* boss) override;
    void update(Boss* boss, float dt) override;
    void exit(Boss* boss) override;

};