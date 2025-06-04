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

//JumpUp
class PlayerJumpUpState : public StateM {
    float time;
    static PlayerJumpUpState* instance;
public:
    static PlayerJumpUpState* getInstance() {
        if (instance == nullptr) {
            instance = new PlayerJumpUpState();
        }

        return instance;
    }

    void enter(Player* player) override;
    void update(Player* player, float dt_) override;
    void exit(Player* player) override;
};

//FallDown
class PlayerFallDownState : public StateM {
    float time;
    static PlayerFallDownState* instance;
public:
    static PlayerFallDownState* getInstance() {
        if (instance == nullptr) {
            instance = new PlayerFallDownState();
        }

        return instance;
    }

    void enter(Player* player) override;
    void update(Player* player, float dt_) override;
    void exit(Player* player) override;
};

//FallDown
class PlayerDashState : public StateM {
    float time;
    static PlayerDashState* instance;
public:
    static PlayerDashState* getInstance() {
        if (instance == nullptr) {
            instance = new PlayerDashState();
        }

        return instance;
    }

    void enter(Player* player) override;
    void update(Player* player, float dt_) override;
    void exit(Player* player) override;
};