#pragma once
#include "BossStateM.h"
#include "Ziz.h"
#include "Level.h"

class Ziz;


class ZizSwoopState : public BossStateM {
private:
    static ZizSwoopState* instance;

    int swoopDirection; //-1 for left, 1 for right
    bool hasFlew;
    bool isOffScreen;
    bool isDisplayingWarning;
    bool hasDisplayedWarning;
    
    float beforeWarningTimer = 1.0f;


    Ziz* ziz;

public:

    static ZizSwoopState* getInstance();

    void enter(Boss* boss) override;
    void update(Boss* boss, float dt) override;
    void exit(Boss* boss) override;

};
