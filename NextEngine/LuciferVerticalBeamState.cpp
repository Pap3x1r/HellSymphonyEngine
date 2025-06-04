#include "LuciferVerticalBeamState.h"

LuciferVerticalBeamState* LuciferVerticalBeamState::instance = nullptr;

LuciferVerticalBeamState* LuciferVerticalBeamState::getInstance() {
    if (!instance) {
        instance = new LuciferVerticalBeamState();
    }
    return instance;
}

void LuciferVerticalBeamState::enter(Boss* boss) {
    lucifer = Lucifer::getInstance();
    

    VerticalIceBeam* vertBeam = new VerticalIceBeam(true);
    lucifer->getLevel()->addObject(vertBeam);

    VerticalIceBeam* vertBeam2 = new VerticalIceBeam(false);
    lucifer->getLevel()->addObject(vertBeam2);
    timer = 2.5f;
}

void LuciferVerticalBeamState::update(Boss* boss, float dt) {
    if (timer > 0) {
        timer -= dt;
        if (timer <= 0) {
            lucifer->getStateMachine()->changeState(LuciferIdleState::getInstance(), lucifer);
        }
    }
    
}

void LuciferVerticalBeamState::exit(Boss* boss) {

}
