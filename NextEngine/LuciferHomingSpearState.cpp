#include "LuciferHomingSpearState.h"

LuciferHomingSpearState* LuciferHomingSpearState::instance = nullptr;

LuciferHomingSpearState* LuciferHomingSpearState::getInstance() {
    if (!instance) {
        instance = new LuciferHomingSpearState();
    }
    return instance;
}

void LuciferHomingSpearState::enter(Boss* boss) {
    lucifer = Lucifer::getInstance();
    

    slotPositions = { -6.0f, -4.0f, -2.0f, 2.0f, 4.0f, 6.0f };
    nextSpearIndex = 0;
    spawnTimer = 0.0f; // ready to spawn first
    delayBetweenSpears = 0.4f; // customize this

    totalDuration = delayBetweenSpears * slotPositions.size() + 3.0f;
}

void LuciferHomingSpearState::update(Boss* boss, float dt) {
    totalDuration -= dt;

    if (nextSpearIndex < slotPositions.size()) {
        spawnTimer -= dt;

        if (spawnTimer <= 0.0f) {
            float pos = slotPositions[nextSpearIndex];
            IceSpear* iceSpearHoming = new IceSpear(lucifer->getPlayer(), pos);
            lucifer->getLevel()->addObject(iceSpearHoming);

            nextSpearIndex++;
            spawnTimer = delayBetweenSpears;
        }
    }

    if (totalDuration <= 0.0f) {
        lucifer->getStateMachine()->changeState(LuciferIdleState::getInstance(), lucifer);
    }
}

void LuciferHomingSpearState::exit(Boss* boss) {
    //cout << "out of homing" << endl;
}
