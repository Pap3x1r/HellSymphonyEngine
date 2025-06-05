#include "LuciferSideLaserState.h"

LuciferSideLaserState* LuciferSideLaserState::instance = nullptr;

LuciferSideLaserState* LuciferSideLaserState::getInstance() {
    if (!instance) {
        instance = new LuciferSideLaserState();
    }
    return instance;
}

void LuciferSideLaserState::enter(Boss* boss) {
    lucifer = Lucifer::getInstance();


    SideStaff* ss = new SideStaff();
    lucifer->getLevel()->addObject(ss);

    timer = 0.08f * 33;

    SoundManager::GetInstance()->PlaySFX("Lucifer-HorizontalBeam");
}

void LuciferSideLaserState::update(Boss* boss, float dt) {
    if (timer > 0) {
        timer -= dt;
        if (timer <= 0) {
            lucifer->getStateMachine()->changeState(LuciferIdleState::getInstance(), lucifer);
        }
    }

}

void LuciferSideLaserState::exit(Boss* boss) {

}
