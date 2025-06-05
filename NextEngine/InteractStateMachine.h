#pragma once

class InteractStateM;
class InteractableObject;

class InteractStateMachine {
private:
    InteractStateM* currentState = nullptr;

public:
    InteractStateMachine();
    ~InteractStateMachine();
    void changeState(InteractStateM* newState, InteractableObject* obj);
    void update(InteractableObject* obj, float dt);
};