#include "LuciferBeamRadiantState.h"

LuciferBeamRadiantState* LuciferBeamRadiantState::instance = nullptr;

LuciferBeamRadiantState* LuciferBeamRadiantState::getInstance() {
    if (!instance) {
        instance = new LuciferBeamRadiantState();
    }
    return instance;
}

void LuciferBeamRadiantState::enter(Boss* boss) {
    lucifer = Lucifer::getInstance();


    BeamRadiant* bm = new BeamRadiant();
    lucifer->getLevel()->addObject(bm);
    SoundManager::GetInstance()->PlaySFX("Lucifer-BeamRadiant_Summon");
    timer = 0.08f * 33;
}

void LuciferBeamRadiantState::update(Boss* boss, float dt) {
    if (timer > 0) {
        timer -= dt;
        if (timer <= 0) {
            lucifer->getStateMachine()->changeState(LuciferIdleState::getInstance(), lucifer);
        }
    }

}

void LuciferBeamRadiantState::exit(Boss* boss) {

}
