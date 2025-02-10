#pragma once
#include "StateM.h"

class Player;

//Idle
class PlayerIdleState : public StateM {
    float time;
    static PlayerIdleState* instance;
public:
    static PlayerIdleState* getInstance() {
        if (instance == nullptr) {
            instance = new PlayerIdleState();
        }

        return instance;
    }

    void enter(Player* player) override;
    void update(Player* player, float dt_) override;
    void exit(Player* player) override;
};


//Walk
class PlayerWalkState : public StateM {
    float time;
    static PlayerWalkState* instance;
public:
    static PlayerWalkState* getInstance() {
        if (instance == nullptr) {
            instance = new PlayerWalkState();
        }

        return instance;
    }

    void enter(Player* player) override;
    void update(Player* player, float dt_) override;
    void exit(Player* player) override;
};