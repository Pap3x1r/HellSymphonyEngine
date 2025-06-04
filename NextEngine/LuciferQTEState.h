#pragma once
#include "BossStateM.h"
#include "Lucifer.h"
#include "Player.h"
#include "QTEManager.h"
#include "QTEButtonUI.h"
#include "LuciferFreeHitState.h"
#include <vector>

class Lucifer;

class LuciferQTEState : public BossStateM {
private:

    static LuciferQTEState* instance;

    Lucifer* lucifer;
    Player* player;

    float bufferTimerFailure;
    float bufferTimerSuccess;

    float timer;
    float timer1;
    float timer2;
    float timer3;

    bool failedAny;
    int currentSeq;

    int QTETarget;
    int QTETarget1;
    int QTETarget2;
    int QTETarget3;

    QTEButtonUI* qteButtonUI;

    float waitSpear;


public:
    static LuciferQTEState* getInstance();

    void enter(Boss* boss) override;
    void update(Boss* boss, float dt) override;
    void exit(Boss* boss) override;

    void randomQTETarget();
    void randomQTESequence();
    void startQTE(int target);

};