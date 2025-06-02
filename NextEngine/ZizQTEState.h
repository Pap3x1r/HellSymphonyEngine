#pragma once
#include "BossStateM.h"
#include "Ziz.h"
#include "Player.h"
#include "ZizIdleState.h"
#include "QTEManager.h"
#include <vector>

class Ziz;

class ZizQTEState : public BossStateM {
private:

    static ZizQTEState* instance;

    Ziz* ziz;
    Player* player;

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
    


public:
    static ZizQTEState* getInstance();

    void enter(Boss* boss) override;
    void update(Boss* boss, float dt) override;
    void exit(Boss* boss) override;

    void randomQTETarget();
    void randomQTESequence();
    void startQTE(int target);

};