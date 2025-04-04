#include "ZizTransitionState.h"
#include "Ziz.h"


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

    ziz->setTexture("../Resource/Ziz/Idle.png");
    transitionTimer = 0.08 * 15;
    transforming = true;
    transformed = false;
    bufferTimer = 0.08 * 36;
    
}

void ZizTransitionState::update(Boss* boss, float dt) {
    if (!ziz) return;
    
    if (transforming == true) {
        if (transformed == false) {
            if (transitionTimer > 0) {
                transitionTimer -= dt;
                cout << "transforming" << endl;
            }
            else {
                transformed = true;
                transforming = false;
                cout << "transformed" << endl;
            }
        }
    }

    if (transformed == true && transforming == false) {
        bufferTimer -= dt;
        if (bufferTimer < 0) {
            ziz->changePhase();
            ziz->getStateMachine()->changeState(ZizGroundSlamState::getInstance(), ziz);
        }
    }
    
    
}

void ZizTransitionState::exit(Boss* boss) {
}
