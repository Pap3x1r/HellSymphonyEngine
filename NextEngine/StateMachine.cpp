#include "StateMachine.h"
#include "StateM.h"
#include "Player.h"

StateMachine::StateMachine() {}

StateMachine::~StateMachine() {
    delete currentState;
}

void StateMachine::changeState(StateM* newState, Player* player, bool override) {
    if (!override) {
        if (currentState == newState) {
            return;
        }
    }
   
    if (currentState) {
        currentState->exit(player);
    }
    currentState = newState;
    if (currentState) {
        currentState->enter(player);
    }
}

void StateMachine::update(Player* player, float dt) {
    if (currentState) {
        currentState->update(player, dt);
    }
}

StateM* StateMachine::getCurrentState() const {
    return currentState;
}