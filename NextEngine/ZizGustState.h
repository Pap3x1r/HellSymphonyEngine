#pragma once
#include "BossStateM.h"

class Ziz;


class ZizGustState : public BossStateM {
private:
    static ZizGustState* instance;
    float gustTimer;
    float gustWaitTime;
    float gustRecoveryTime;

public:
    
    static ZizGustState* getInstance();

    void enter(Boss* boss) override;
    void update(Boss* boss, float dt) override;
    void exit(Boss* boss) override;

};