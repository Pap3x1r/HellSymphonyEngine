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
    ziz = dynamic_cast<Ziz*>(boss);
    if (!ziz) return;

    player = ziz->getPlayer();
    if (player) {
        //cout << "found Player" << endl;
    }

    idleTimer = 0.08f * 10;
    //ziz->setTexture("../Resource/Ziz/Idle.png");
    ziz->setTexture("../Resource/Texture/FinalZiz/Zyzz_Idle-Sheet.png", 1, 10, 0);
    //ziz->setTexture("../Resource/Texture/Ziz/Ziz_Idle.png", 1, 10, 0);
    ziz->getAnimationComponent()->setState("idle");
    ziz->facePlayer();
    //cout << "Ziz entered Idle State.\n";
}

void ZizIdleState::update(Boss* boss, float dt) {
    if (!ziz) return;

    if (idleTimer > 0) {
        idleTimer -= dt;
    }
    else {
        ziz->getStateMachine()->changeState(ZizChompState::getInstance(), ziz);
        //ziz->getStateMachine()->changeState(ZizIdleState::getInstance(), ziz);
        //pickState();
    }

}

void ZizIdleState::exit(Boss* boss) {
    //cout << "Ziz exiting Idle State.\n";
}

void ZizIdleState::pickState() {
    float distance = abs(ziz->getTransform().getPosition().x - player->getTransform().getPosition().x);
    float randValue = static_cast<float>(rand()) / RAND_MAX;

    if (ziz->getPhase() == 1) {//phase 1
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
    else if (ziz->getPhase() == 2) {
        if (distance > 4.0f) { // **Far Distance Attacks**
            if (randValue < 0.60f) {
                ziz->getStateMachine()->changeState(ZizSwoopState::getInstance(), ziz);
            }
            else {
                ziz->getStateMachine()->changeState(ZizGroundSlamState::getInstance(), ziz);
            }
        }
        else { // **Close Distance Attacks**
            if (randValue < 0.35f) {
                ziz->getStateMachine()->changeState(ZizClawSlashState::getInstance(), ziz);
            }
            else if (randValue < 0.65f) {
                ziz->getStateMachine()->changeState(ZizGroundSlamState::getInstance(), ziz);
            }
            else {
                ziz->getStateMachine()->changeState(ZizChompState::getInstance(), ziz);
            }
        }
    }

    
}
