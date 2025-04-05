#include "ZizDeathState.h"
#include "Ziz.h"


ZizDeathState* ZizDeathState::instance = nullptr;

ZizDeathState* ZizDeathState::getInstance() {
    if (!instance) {
        instance = new ZizDeathState();
    }
    return instance;
}

void ZizDeathState::enter(Boss* boss) {
    ziz = dynamic_cast<Ziz*>(boss);
    if (!ziz) return;

    player = ziz->getPlayer();
    if (player) {
        //cout << "found Player" << endl;
    }

    deathTimer = 0.08f * 10;
    //ziz->setTexture("../Resource/Ziz/Idle.png");

    ziz->setTexture("../Resource/Texture/Ziz/Ziz_Idle.png", 1, 10, 0);
    ziz->getAnimationComponent()->setState("idle");
    ziz->facePlayer();
    //cout << "Ziz entered Idle State.\n";
}

void ZizDeathState::update(Boss* boss, float dt) {
    if (!ziz) return;

    if (deathTimer > 0) {
        deathTimer -= dt;
    }
    else {
        ziz->getStateMachine()->changeState(ZizDeathState::getInstance(), ziz);
        //ziz->getStateMachine()->changeState(ZizIdleState::getInstance(), ziz);
    }

}

void ZizDeathState::exit(Boss* boss) {
    //cout << "Ziz exiting Idle State.\n";
}


