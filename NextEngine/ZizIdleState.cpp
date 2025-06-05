#include "ZizIdleState.h"
#include "Ziz.h"
#include "ZizTransitionState.h"


ZizIdleState* ZizIdleState::instance = nullptr;

ZizIdleState* ZizIdleState::getInstance() {
    if (!instance) {
        instance = new ZizIdleState();
    }
    return instance;
}

void ZizIdleState::enter(Boss* boss) {
    ziz = Ziz::getInstance();

    player = ziz->getPlayer();

    

    idleTimer = 0.08f * 10;
    
    ziz->setTexture("../Resource/Texture/FinalZiz/Zyzz_Idle-Sheet.png", 1, 10, 0);
    
    ziz->getAnimationComponent()->setState("idle");
    ziz->facePlayer();
    SoundManager::GetInstance()->PlaySFX("Ziz_Idle");
}

void ZizIdleState::update(Boss* boss, float dt) {
    if (!ziz) return;

    if (idleTimer > 0) {
        idleTimer -= dt;
    }
    else {
        //ziz->getStateMachine()->changeState(ZizTransitionState::getInstance(), ziz);
        //ziz->getStateMachine()->changeState(ZizIdleState::getInstance(), ziz);
        pickState();
    }
}

void ZizIdleState::exit(Boss* boss) {
    //cout << "Ziz exiting Idle State.\n";
}

void ZizIdleState::pickState() {
    float randValue = (rand() % 11);
    //cout << "Rand In Idle: " << randValue << endl;


    if (ziz->getCurrentPhase() == 1) {//phase 1
        if (ziz->getDistanceFromPlayer() > 4.0f) { // **Far Distance Attacks**
            if (randValue < 3.0f) {
                //cout << "gust" << endl;
                ziz->getStateMachine()->changeState(ZizGustState::getInstance(), ziz);
            }
            else if (randValue < 6.0f) {
                //cout << "swoop" << endl;
                ziz->getStateMachine()->changeState(ZizSwoopState::getInstance(), ziz);
            }
            else if (randValue < 8.0f) {
                //cout << "slam" << endl;
                ziz->getStateMachine()->changeState(ZizGroundSlamState::getInstance(), ziz);
            }
            else {
                //cout << "stormrise" << endl;
                ziz->getStateMachine()->changeState(ZizStormRiseState::getInstance(), ziz);
            }
        }
        else { // **Close Distance Attacks**
            if (randValue < 3.0f) {
                //cout << "clawslash" << endl;
                ziz->getStateMachine()->changeState(ZizClawSlashState::getInstance(), ziz);
            }
            else if (randValue < 6.0f){
                //cout << "swoop" << endl;
                ziz->getStateMachine()->changeState(ZizWingSpanState::getInstance(), ziz);
            }
            else {
                if (rand() % 2 == 0) {
                    ziz->getStateMachine()->changeState(ZizQTEState::getInstance(), ziz);
                }
                else {
                    ziz->getStateMachine()->changeState(ZizSwoopState::getInstance(), ziz);
                }
                
            }
        }
    }
    else if (ziz->getCurrentPhase() == 2) {
        if (ziz->getDistanceFromPlayer() > 4.0f) { // **Far Distance Attacks**
            if (randValue < 6.0f) {
                ziz->getStateMachine()->changeState(ZizSwoopState::getInstance(), ziz);
            }
            else {
                ziz->getStateMachine()->changeState(ZizGroundSlamState::getInstance(), ziz);
            }
        }
        else { // **Close Distance Attacks**
            if (randValue < 3.5f) {
                ziz->getStateMachine()->changeState(ZizClawSlashState::getInstance(), ziz);
            }
            else if (randValue < 6.5f) {
                ziz->getStateMachine()->changeState(ZizGroundSlamState::getInstance(), ziz);
            }
            else {
                ziz->getStateMachine()->changeState(ZizChompState::getInstance(), ziz);
            }
        }
    }

    
}
