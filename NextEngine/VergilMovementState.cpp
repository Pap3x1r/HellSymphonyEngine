#include "VergilMovementState.h"
#include "InteractableObject.h"

VergilIdleState* VergilIdleState::instance = nullptr;
VergilHightlightState* VergilHightlightState::instance = nullptr;

//Idle
void VergilIdleState::enter(InteractableObject* obj) {
    //cout << "Player enters Idle state.\n";
    obj->setTexture("../Resource/Texture/Interactables/Vergil idle-Sheet.png", 1, 8, 0);
    obj->getAnimationComponent()->setState("idle");
}

void VergilIdleState::update(InteractableObject* obj, float dt_) {
    time += dt_;
    //cout << "Player Idle State: " << time << " (total dt)\n";

    
    /*if (time > 0.12f) {
        player->getAnimationComponent()->updateCurrentState();
        time = 0;
    }*/
}

void VergilIdleState::exit(InteractableObject* obj) {
    //cout << "Player exits Idle state.\n";
}

//Idle
void VergilHightlightState::enter(InteractableObject* obj) {
    //cout << "Player enters Idle state.\n";
    obj->setTexture("../Resource/Texture/Interactables/Vergil idle-Outlined.png", 1, 8, 0);
    obj->getAnimationComponent()->setState("highlight");
}

void VergilHightlightState::update(InteractableObject* obj, float dt_) {
    time += dt_;
    //cout << "Player Idle State: " << time << " (total dt)\n";


    /*if (time > 0.12f) {
        player->getAnimationComponent()->updateCurrentState();
        time = 0;
    }*/
}

void VergilHightlightState::exit(InteractableObject* obj) {
    //cout << "Player exits Idle state.\n";
}