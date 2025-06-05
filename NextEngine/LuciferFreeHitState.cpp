#include "LuciferFreeHitState.h"
#include "Lucifer.h"



LuciferFreeHitState* LuciferFreeHitState::instance = nullptr;

LuciferFreeHitState* LuciferFreeHitState::getInstance() {
    if (!instance) {
        instance = new LuciferFreeHitState();
    }
    return instance;
}

void LuciferFreeHitState::enter(Boss* boss) {
    lucifer = Lucifer::getInstance();

    idleTimer = 3.0f;

    //cout << "Lucifer Idle Enter" << endl;
}

void LuciferFreeHitState::update(Boss* boss, float dt) {

    if (idleTimer > 0) {
        idleTimer -= dt;
    }
    else {

        lucifer->getStateMachine()->changeState(LuciferIdleState::getInstance(), lucifer);
    }
}

void LuciferFreeHitState::exit(Boss* boss) {

}
