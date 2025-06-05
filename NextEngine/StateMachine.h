#pragma once

class StateM;
class Player;

class StateMachine {
private:
    StateM* currentState = nullptr;

public:
    StateMachine();
    ~StateMachine();
    void changeState(StateM* newState, Player* player, bool override = false);
    void update(Player* player, float dt);
    StateM* getCurrentState() const;
};