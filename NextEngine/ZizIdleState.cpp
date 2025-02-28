#include "ZizIdleState.h"
#include "Ziz.h"
#include "ZizGustState.h"
#include "ZizSwoopState.h"

ZizIdleState* ZizIdleState::instance = nullptr;

ZizIdleState* ZizIdleState::getInstance() {
    if (!instance) {
        instance = new ZizIdleState();
    }
    return instance;
}

void ZizIdleState::enter(Boss* boss) {
    Ziz* ziz = dynamic_cast<Ziz*>(boss);
    if (!ziz) return;

    idleTimer = 0.0f;
    ziz->setTexture("../Resource/Ziz/Idle.png");
    ziz->facePlayer();
    //std::cout << "Ziz entered Idle State.\n";
}

void ZizIdleState::update(Boss* boss, float dt) {
    Ziz* ziz = dynamic_cast<Ziz*>(boss);
    if (!ziz) return;

    idleTimer += dt;

    // Ziz Timer for idle
    if (idleTimer >= idleWaitTime) {
        //std::cout << "Ziz has idled, resetting state.\n";
        ziz->getStateMachine()->changeState(ZizSwoopState::getInstance(), ziz);
    }

    //std::cout << "Ziz is idling...\n";
}

void ZizIdleState::exit(Boss* boss) {
    //std::cout << "Ziz exiting Idle State.\n";
}
