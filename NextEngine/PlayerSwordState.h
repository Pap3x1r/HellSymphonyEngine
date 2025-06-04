#pragma once
#include "StateM.h"

class Player;

//Light Sword Attack 1
class PlayerLightSwordAttack1 : public StateM {
    float time;

    static PlayerLightSwordAttack1* instance;

    enum Phase { STARTUP, ACTIVE, RECOVERY };
    Phase currentPhase;
public:
    static PlayerLightSwordAttack1* getInstance() {
        if (instance == nullptr) {
            instance = new PlayerLightSwordAttack1();
        }

        return instance;
    }

    void enter(Player* player) override;
    void update(Player* player, float dt_) override;
    void exit(Player* player) override;
};


//Light Sword Attack 2
class PlayerLightSwordAttack2 : public StateM {
    float time;

    static PlayerLightSwordAttack2* instance;

    enum Phase { STARTUP, ACTIVE, RECOVERY };
    Phase currentPhase;
public:
    static PlayerLightSwordAttack2* getInstance() {
        if (instance == nullptr) {
            instance = new PlayerLightSwordAttack2();
        }

        return instance;
    }

    void enter(Player* player) override;
    void update(Player* player, float dt_) override;
    void exit(Player* player) override;
};

//Light Sword Attack 3
class PlayerLightSwordAttack3 : public StateM {
    float time;

    static PlayerLightSwordAttack3* instance;

    enum Phase { STARTUP, ACTIVE, RECOVERY };
    Phase currentPhase;
public:
    static PlayerLightSwordAttack3* getInstance() {
        if (instance == nullptr) {
            instance = new PlayerLightSwordAttack3();
        }

        return instance;
    }

    void enter(Player* player) override;
    void update(Player* player, float dt_) override;
    void exit(Player* player) override;
};


//Heavy Sword Attack
class PlayerHeavySwordAttack : public StateM {
    float time;

    static PlayerHeavySwordAttack* instance;

    enum Phase { STARTUP, ACTIVE, RECOVERY };
    Phase currentPhase;
public:
    static PlayerHeavySwordAttack* getInstance() {
        if (instance == nullptr) {
            instance = new PlayerHeavySwordAttack();
        }

        return instance;
    }

    void enter(Player* player) override;
    void update(Player* player, float dt_) override;
    void exit(Player* player) override;
};

//Small Sword Ult
class PlayerSmallSwordUlt : public StateM {
    float time;

    static PlayerSmallSwordUlt* instance;

    enum Phase { STARTUP, ACTIVE, RECOVERY };
    Phase currentPhase;
public:
    static PlayerSmallSwordUlt* getInstance() {
        if (instance == nullptr) {
            instance = new PlayerSmallSwordUlt();
        }

        return instance;
    }

    void enter(Player* player) override;
    void update(Player* player, float dt_) override;
    void exit(Player* player) override;
};

//Big Sword Ult
class PlayerBigSwordUlt : public StateM {
    float time;
    float time2;
    static PlayerBigSwordUlt* instance;

    enum Phase { STARTUP, ACTIVE, RECOVERY, ONE, TWO, THREE, FOUR, FIVE };
    Phase currentPhase;
    Phase currentPhase2;
public:
    static PlayerBigSwordUlt* getInstance() {
        if (instance == nullptr) {
            instance = new PlayerBigSwordUlt();
        }

        return instance;
    }

    void enter(Player* player) override;
    void update(Player* player, float dt_) override;
    void exit(Player* player) override;
};