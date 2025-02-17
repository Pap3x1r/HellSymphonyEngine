#include "BossStateMachine.h"
#include "BossStateM.h"
#include "Boss.h"

BossStateMachine::BossStateMachine() {}

BossStateMachine::~BossStateMachine() {
    delete currentState;
}

void BossStateMachine::changeState(BossStateM* newState, Boss* boss) {
    if (currentState) {
        currentState->exit(boss);
    }
    currentState = newState;
    if (currentState) {
        currentState->enter(boss);
    }
}

void BossStateMachine::update(Boss* boss, float dt) {
    if (currentState) {
        currentState->update(boss, dt);
    }
}