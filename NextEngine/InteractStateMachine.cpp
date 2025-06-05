#include "InteractStateMachine.h"
#include "InteractStateM.h"
#include "InteractableObject.h"

InteractStateMachine::InteractStateMachine() {}

InteractStateMachine::~InteractStateMachine() {
    delete currentState;
}

void InteractStateMachine::changeState(InteractStateM* newState, InteractableObject* obj) {
    if (currentState == newState) {
        return;
    }

    if (currentState) {
        currentState->exit(obj);
    }
    currentState = newState;
    if (currentState) {
        currentState->enter(obj);
    }
}

void InteractStateMachine::update(InteractableObject* obj, float dt) {
    if (currentState) {
        currentState->update(obj, dt);
    }
}