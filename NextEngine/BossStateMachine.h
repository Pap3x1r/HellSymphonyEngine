#pragma once

class BossStateM;
class Boss;

class BossStateMachine {
private:
    BossStateM* currentState = nullptr;

public:
    BossStateMachine();
    ~BossStateMachine();
    void changeState(BossStateM* newState, Boss* boss);
    void update(Boss* boss, float dt);
};