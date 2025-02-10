#pragma once
#include "StateM.h"

class Player;

//Idle
class PlayerLightBowAttack : public StateM {
    float time;

    static PlayerLightBowAttack* instance;

    enum Phase { STARTUP, ACTIVE, RECOVERY };
    Phase currentPhase;
public:
    static PlayerLightBowAttack* getInstance() {
        if (instance == nullptr) {
            instance = new PlayerLightBowAttack();
        }

        return instance;
    }

    void enter(Player* player) override;
    void update(Player* player, float dt_) override;
    void exit(Player* player) override;
};


//Walk
class PlayerHeavyBowAttack : public StateM {
    float time;

    static PlayerHeavyBowAttack* instance;

    enum Phase { STARTUP, ACTIVE, RECOVERY };
    Phase currentPhase;
public:
    static PlayerHeavyBowAttack* getInstance() {
        if (instance == nullptr) {
            instance = new PlayerHeavyBowAttack();
        }

        return instance;
    }

    void enter(Player* player) override;
    void update(Player* player, float dt_) override;
    void exit(Player* player) override;
};