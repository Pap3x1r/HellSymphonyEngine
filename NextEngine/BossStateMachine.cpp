#include "BossStateMachine.h"
#include "BossStateM.h"
#include "Boss.h"
#include "ZizIdleState.h"
#include "ZizGustState.h"
#include "ZizSwoopState.h"
#include "ZizGroundSlamState.h"
#include "ZizWingSpanState.h"
#include "ZizClawSlashState.h"
#include "ZizChompState.h"
#include "ZizTransitionState.h"
#include "ZizImpaleState.h"
#include "ZizQTEState.h"

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

void BossStateMachine::interruptPhaseChange(Boss* boss) {
    if (currentState) {


        if (currentState == ZizGroundSlamState::getInstance()) {
            cout << "Interrupted from GroundSlam" << endl;
            boss->getTransform().setPosition(boss->getTransform().getPosition().x, 0.05f);
        }

        if (currentState == ZizSwoopState::getInstance()) {
            cout << "Interrupted from Swoop" << endl;
            boss->getTransform().setPosition(boss->getTransform().getPosition().x, 0.05f);
        }

        currentState->exit(boss);
    }
    currentState = ZizTransitionState::getInstance();
    if (currentState) {
        currentState->enter(boss);
    }
}

void BossStateMachine::interruptDeath(Boss* boss) {

}

void BossStateMachine::interruptIntoPhase(Boss* boss) {
    if (currentState) {


        if (currentState == ZizGroundSlamState::getInstance()) {
            cout << "Interrupted from GroundSlam" << endl;
            boss->getTransform().setPosition(boss->getTransform().getPosition().x, 0.05f);
        }

        if (currentState == ZizSwoopState::getInstance()) {
            cout << "Interrupted from Swoop" << endl;
            boss->getTransform().setPosition(boss->getTransform().getPosition().x, 0.05f);
        }

        currentState->exit(boss);
    }
    currentState = ZizQTEState::getInstance();
    if (currentState) {
        currentState->enter(boss);
    }
}

void BossStateMachine::update(Boss* boss, float dt) {
    if (currentState) {
        currentState->update(boss, dt);
    }
}

BossStateM* BossStateMachine::getCurrentState() {
    return currentState;
}