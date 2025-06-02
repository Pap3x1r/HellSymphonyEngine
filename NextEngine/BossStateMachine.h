#pragma once

class BossStateM;
class Boss;

class BossStateMachine {
private:
    BossStateM* currentState = nullptr;
    BossStateM* nextState = nullptr;

public:
    BossStateMachine();
    ~BossStateMachine();
    void changeState(BossStateM* newState, Boss* boss);
    void update(Boss* boss, float dt);
    void interruptPhaseChange(Boss* boss);
    void interruptDeath(Boss* boss);
    void interruptIntoPhase(Boss* boss);
    BossStateM* getCurrentState();
};