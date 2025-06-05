#pragma once
#include "BossStateM.h"
#include "Ziz.h"
#include "Impale.h"
#include "Level.h"

class Ziz;

class ZizImpaleState : public BossStateM {
private:
    static ZizImpaleState* instance;
    Ziz* ziz;

    float delayBeforeImpale;
    bool hasImpaled;
    int timesSummonedImpale;
    float delayAfterImpale;
    float poseTimer;
    bool hasRecovered;

public:

    static ZizImpaleState* getInstance();

    void enter(Boss* boss) override;
    void update(Boss* boss, float dt) override;
    void exit(Boss* boss) override;

};