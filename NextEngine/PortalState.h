#pragma once
#include "InteractStateM.h"

class InteractableObject;

//Idle
class PortalIdleState : public InteractStateM {
    float time;
    static PortalIdleState* instance;
public:
    static PortalIdleState* getInstance() {
        if (instance == nullptr) {
            instance = new PortalIdleState();
        }

        return instance;
    }

    void enter(InteractableObject* obj) override;
    void update(InteractableObject* obj, float dt_) override;
    void exit(InteractableObject* obj) override;
};