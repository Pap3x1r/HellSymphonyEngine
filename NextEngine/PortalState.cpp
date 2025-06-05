#include "PortalState.h"
#include "InteractableObject.h"

PortalIdleState* PortalIdleState::instance = nullptr;

//Idle
void PortalIdleState::enter(InteractableObject* obj) {
    //cout << "Player enters Idle state.\n";
    obj->setTexture("../Resource/Texture/Interactables/Portal-Sheet.png", 1, 19, 0);
    obj->getAnimationComponent()->setState("idle");
}

void PortalIdleState::update(InteractableObject* obj, float dt_) {
    time += dt_;
    //cout << "Player Idle State: " << time << " (total dt)\n";


    /*if (time > 0.12f) {
        player->getAnimationComponent()->updateCurrentState();
        time = 0;
    }*/
}

void PortalIdleState::exit(InteractableObject* obj) {
    //cout << "Player exits Idle state.\n";
}