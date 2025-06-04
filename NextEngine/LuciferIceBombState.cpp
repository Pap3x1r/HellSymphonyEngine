#include "LuciferIceBombState.h"

LuciferIceBombState* LuciferIceBombState::instance = nullptr;

LuciferIceBombState* LuciferIceBombState::getInstance() {
    if (!instance) {
        instance = new LuciferIceBombState();
    }
    return instance;
}

void LuciferIceBombState::enter(Boss* boss) {
    lucifer = Lucifer::getInstance();
    timer = 3.0f;

    slotPositions = { -6.0f, -4.0f, -2.0f, 0.0f, 2.0f, 4.0f, 6.0f };
    nextBombIndex = 0;
    spawnTimer = 0.0f; // ready to spawn first
    delayBetweenBombs = 0.4f; // customize this

    totalDuration = delayBetweenBombs * slotPositions.size() + 1.0f;
}

void LuciferIceBombState::update(Boss* boss, float dt) {
    totalDuration -= dt;

    if (nextBombIndex < slotPositions.size()) {
        spawnTimer -= dt;

        if (spawnTimer <= 0.0f) {
            float pos = slotPositions[nextBombIndex];
            IceBomb* iceBomb = new IceBomb(pos);
            lucifer->getLevel()->addObject(iceBomb);

            nextBombIndex++;
            spawnTimer = delayBetweenBombs;
        }
    }

    if (totalDuration <= 0.0f) {
        lucifer->getStateMachine()->changeState(LuciferIdleState::getInstance(), lucifer);
    }
}

void LuciferIceBombState::exit(Boss* boss) {
    
}
