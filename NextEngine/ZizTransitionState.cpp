#include "ZizTransitionState.h"
#include "Ziz.h"
#include "ZizUltState.h"


ZizTransitionState* ZizTransitionState::instance = nullptr;

ZizTransitionState* ZizTransitionState::getInstance() {
    if (!instance) {
        instance = new ZizTransitionState();
    }
    return instance;
}

void ZizTransitionState::enter(Boss* boss) {
    ziz = dynamic_cast<Ziz*>(boss);
    if (!ziz) return;

    //ziz->setTexture("../Resource/Ziz/Idle.png");
    ziz->setTexture("../Resource/Texture/FinalZiz/Starting Phase/Transform.png", 1, 33, 0);
    ziz->getAnimationComponent()->setState("transform");
    transitionTimer = 0.08 * 33;
    transforming = true;
    transformed = false;
    bufferTimer = 0.08 * 0;
    ziz->setIsInvincible(true);
    //33 frames
}

void ZizTransitionState::update(Boss* boss, float dt) {
    if (!ziz) return;
    
    if (transforming == true) {
        if (transformed == false) {
            if (transitionTimer > 0) {
                transitionTimer -= dt;
                if (transitionTimer <= 2.24f && transitionTimer > 2.0f) {
                    ziz->startShake(0.08f * 16, 0.005f);
                }

                //cout << "transforming" << endl;
            }
            else {
                transformed = true;
                transforming = false;
                //cout << "transformed" << endl;
            }
        }
    }

    if (transformed == true && transforming == false) {
        bufferTimer -= dt;
        if (bufferTimer < 0) {
            ziz->changePhase();
            ziz->getStateMachine()->changeState(ZizUltState::getInstance(), ziz);
        }
    }
    
    
}

void ZizTransitionState::exit(Boss* boss) {
    ziz->setIsInvincible(false);
}
