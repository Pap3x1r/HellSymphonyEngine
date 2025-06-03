#pragma once

class LuciferStateM;
class Boss;

class LuciferStateMachine {
private:
    LuciferStateM* currentState = nullptr;
    LuciferStateM* nextState = nullptr;

public:
    LuciferStateMachine();
    ~LuciferStateMachine();
    void changeState(LuciferStateM* newState, Boss* boss);
    void update(Boss* boss, float dt);
    LuciferStateM* getCurrentState();
};