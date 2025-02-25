#include "ZizIdleState.h"
#include "Ziz.h"

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

    
    ziz->getAnimationComponent()->setState("idle");
    ziz->getPhysicsComponent()->setVelocity(glm::vec2(0, 0));
    idleTimer = 0.0f;

    std::cout << "Ziz entered Idle State.\n";
}

void ZizIdleState::update(Boss* boss, float dt) {
    Ziz* ziz = dynamic_cast<Ziz*>(boss);
    if (!ziz) return;

    idleTimer += dt;

    // Ziz Timer for idle
    if (idleTimer >= idleWaitTime) {
        std::cout << "Ziz has idled for 5 seconds, resetting state.\n";
        ziz->getStateMachine()->changeState(ZizIdleState::getInstance(), ziz);
    }

    //std::cout << "Ziz is idling...\n";
}

void ZizIdleState::exit(Boss* boss) {
    std::cout << "Ziz exiting Idle State.\n";
}
