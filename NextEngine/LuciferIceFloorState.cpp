#include "LuciferIceFloorState.h"

LuciferIceFloorState* LuciferIceFloorState::instance = nullptr;

LuciferIceFloorState* LuciferIceFloorState::getInstance() {
    if (!instance) {
        instance = new LuciferIceFloorState();
    }
    return instance;
}

void LuciferIceFloorState::enter(Boss* boss) {
    lucifer = Lucifer::getInstance();

    hasSpawnedFloor = false;
    spawnFloor = 1.0f;
    timer = 0.08f * 17;

    IceFloorWarning* iFW = new IceFloorWarning();
    lucifer->getLevel()->addObject(iFW);

}

void LuciferIceFloorState::update(Boss* boss, float dt) {
    
    if (hasSpawnedFloor == false) {
        spawnFloor -= dt;
        if (spawnFloor <= 0) {
            IceFloor* iF = new IceFloor();
            lucifer->getLevel()->addObject(iF);
            hasSpawnedFloor = true;
            SoundManager::GetInstance()->PlaySFX("Lucifer-DiamondDust");
        }
    }
    else {
        timer -= dt;
        if (timer <= 0) {
            lucifer->getStateMachine()->changeState(LuciferIdleState::getInstance(), lucifer);
        }
    }

}

void LuciferIceFloorState::exit(Boss* boss) {

}
