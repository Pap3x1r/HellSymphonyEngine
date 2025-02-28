#pragma once
#include "StateM.h"

class Player;

//Light Sword Attack 1
class PlayerLightShieldAttack1 : public StateM {
    float time;

    static PlayerLightShieldAttack1* instance;

    enum Phase { STARTUP, ACTIVE, RECOVERY };
    Phase currentPhase;
public:
    static PlayerLightShieldAttack1* getInstance() {
        if (instance == nullptr) {
            instance = new PlayerLightShieldAttack1();
        }

        return instance;
    }

    void enter(Player* player) override;
    void update(Player* player, float dt_) override;
    void exit(Player* player) override;
};


//Light Sword Attack 2
class PlayerLightShieldAttack2 : public StateM {
    float time;

    static PlayerLightShieldAttack2* instance;

    enum Phase { STARTUP, ACTIVE, RECOVERY };
    Phase currentPhase;
public:
    static PlayerLightShieldAttack2* getInstance() {
        if (instance == nullptr) {
            instance = new PlayerLightShieldAttack2();
        }

        return instance;
    }

    void enter(Player* player) override;
    void update(Player* player, float dt_) override;
    void exit(Player* player) override;
};

//Guard
class PlayerShieldGuard : public StateM {
    float time;

    static PlayerShieldGuard* instance;

    enum Phase { STARTUP, ACTIVE, RECOVERY };
    Phase currentPhase;
public:
    static PlayerShieldGuard* getInstance() {
        if (instance == nullptr) {
            instance = new PlayerShieldGuard();
        }

        return instance;
    }

    void enter(Player* player) override;
    void update(Player* player, float dt_) override;
    void exit(Player* player) override;
    void changeState(int phase);
};

class PlayerOffShield : public StateM {
    float time;

    static PlayerOffShield* instance;

    enum Phase { STARTUP, ACTIVE, RECOVERY };
    Phase currentPhase;
public:
    static PlayerOffShield* getInstance() {
        if (instance == nullptr) {
            instance = new PlayerOffShield();
        }

        return instance;
    }

    void enter(Player* player) override;
    void update(Player* player, float dt_) override;
    void exit(Player* player) override;
};

class PlayerSmallShieldUlt : public StateM {
    float time;

    static PlayerSmallShieldUlt* instance;

    enum Phase { STARTUP, ACTIVE, RECOVERY };
    Phase currentPhase;
public:
    static PlayerSmallShieldUlt* getInstance() {
        if (instance == nullptr) {
            instance = new PlayerSmallShieldUlt();
        }

        return instance;
    }

    void enter(Player* player) override;
    void update(Player* player, float dt_) override;
    void exit(Player* player) override;
};

class PlayerBigShieldUlt : public StateM {
    float time;

    static PlayerBigShieldUlt* instance;

    enum Phase { STARTUP, ACTIVE, RECOVERY };
    Phase currentPhase;
public:
    static PlayerBigShieldUlt* getInstance() {
        if (instance == nullptr) {
            instance = new PlayerBigShieldUlt();
        }

        return instance;
    }

    void enter(Player* player) override;
    void update(Player* player, float dt_) override;
    void exit(Player* player) override;
};