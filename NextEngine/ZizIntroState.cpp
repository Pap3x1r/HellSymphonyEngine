#include "ZizIntroState.h"

ZizIntroState* ZizIntroState::instance = nullptr;

ZizIntroState* ZizIntroState::getInstance() {
    if (!instance) {
        instance = new ZizIntroState();
    }
    return instance;
}

void ZizIntroState::enter(Boss* boss) {
    ziz = Ziz::getInstance();

    timer = 0.08f * 10;

    ziz->setTexture("../Resource/Texture/FinalZiz/Zyzz_Idle-Sheet.png", 1, 10, 0);
    ziz->getAnimationComponent()->setState("idle");
    ziz->facePlayer();
    ziz->setIsInvincible(true);
}

void ZizIntroState::update(Boss* boss, float dt) {

}

void ZizIntroState::exit(Boss* boss) {

}