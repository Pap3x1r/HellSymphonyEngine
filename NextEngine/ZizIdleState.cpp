#include "ZizIdleState.h"
#include "Ziz.h"
#include "ZizGustState.h"
#include "ZizSwoopState.h"
#include "ZizGroundSlamState.h"
#include "ZizWingSpanState.h"
#include "ZizClawSlashState.h"
#include "ZizChompState.h"

ZizIdleState* ZizIdleState::instance = nullptr;

ZizIdleState* ZizIdleState::getInstance() {
    if (!instance) {
        instance = new ZizIdleState();
    }
    return instance;
}

void ZizIdleState::enter(Boss* boss) {
    ziz = dynamic_cast<Ziz*>(boss);
    if (!ziz) return;

    player = ziz->getPlayer();
    if (player) {
        cout << "found Player" << endl;
    }

    idleTimer = 0.0f;
    ziz->setTexture("../Resource/Ziz/Idle.png");
    ziz->facePlayer();
    //std::cout << "Ziz entered Idle State.\n";
}

void ZizIdleState::update(Boss* boss, float dt) {
    if (!ziz) return;

    idleTimer += dt;

    // Ziz Timer for idle
    if (idleTimer >= idleWaitTime) {
        //std::cout << "Ziz has idled, resetting state.\n";
        ziz->getStateMachine()->changeState(ZizChompState::getInstance(), ziz);
        //pickState();
    }

    //std::cout << "Ziz is idling...\n";
}

void ZizIdleState::exit(Boss* boss) {
    std::cout << "Ziz exiting Idle State.\n";
}

void ZizIdleState::pickState() {
    float distance = abs(ziz->getTransform().getPosition().x - player->getTransform().getPosition().x);
    float randValue = static_cast<float>(rand()) / RAND_MAX;

    if (distance > 4.0f) { // **Far Distance Attacks**
        if (randValue < 0.30f) {
            ziz->getStateMachine()->changeState(ZizGustState::getInstance(), ziz);
        }
        else if (randValue < 0.60f) {
            ziz->getStateMachine()->changeState(ZizSwoopState::getInstance(), ziz);
        }
        else if (randValue < 0.80f) {
            ziz->getStateMachine()->changeState(ZizGroundSlamState::getInstance(), ziz);
        }
        else {
            ziz->getStateMachine()->changeState(ZizStormRiseState::getInstance(), ziz);
        }
    }
    else { // **Close Distance Attacks**
        if (randValue < 0.60f) {
            ziz->getStateMachine()->changeState(ZizClawSlashState::getInstance(), ziz);
        }
        else {
            ziz->getStateMachine()->changeState(ZizWingSpanState::getInstance(), ziz);
        }
    }
}
