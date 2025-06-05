#pragma once
#include "InteractStateM.h"

class InteractableObject;

//Idle
class VergilIdleState : public InteractStateM {
    float time;
    static VergilIdleState* instance;
public:
    static VergilIdleState* getInstance() {
        if (instance == nullptr) {
            instance = new VergilIdleState();
        }

        return instance;
    }

    void enter(InteractableObject* obj) override;
    void update(InteractableObject* obj, float dt_) override;
    void exit(InteractableObject* obj) override;
};

//Idle
class VergilHightlightState : public InteractStateM {
    float time;
    static VergilHightlightState* instance;
public:
    static VergilHightlightState* getInstance() {
        if (instance == nullptr) {
            instance = new VergilHightlightState();
        }

        return instance;
    }

    void enter(InteractableObject* obj) override;
    void update(InteractableObject* obj, float dt_) override;
    void exit(InteractableObject* obj) override;
};