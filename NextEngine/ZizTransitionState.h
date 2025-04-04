#pragma once
#include "BossStateM.h"
#include "Ziz.h"
#include "Player.h"
#include "ZizIdleState.h"

class Ziz;


class ZizTransitionState : public BossStateM {
private:

    static ZizTransitionState* instance;

    Ziz* ziz;
    Player* player;

    float transitionTimer;
    bool transforming;
    bool transformed;
    float bufferTimer;

public:
    static ZizTransitionState* getInstance();

    void enter(Boss* boss) override;
    void update(Boss* boss, float dt) override;
    void exit(Boss* boss) override;

};