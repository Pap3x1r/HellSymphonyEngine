#include "LuciferVerticalBarrageState.h"


LuciferVerticalBarrageState* LuciferVerticalBarrageState::instance = nullptr;

LuciferVerticalBarrageState* LuciferVerticalBarrageState::getInstance() {
    if (!instance) {
        instance = new LuciferVerticalBarrageState();
    }
    return instance;
}

void LuciferVerticalBarrageState::enter(Boss* boss) {
    lucifer = Lucifer::getInstance();
    timer = 3.0f;

    // Define the X positions for the spears
    std::vector<float> slotPositions = { -6.0f, -4.0f, -2.0f, 0.0f, 2.0f, 4.0f, 6.0f };

    // Choose one slot to leave empty
    int emptyIndex = rand() % slotPositions.size();

    for (int i = 0; i < slotPositions.size(); ++i) {
        if (i == emptyIndex) continue;  // Skip the empty slot

        IceSpear* iceSpear = new IceSpear(FacingDirection::down, slotPositions[i]);
        //iceSpear->getTransform().setPosition(glm::vec3(slotPositions[i], 8.0f, 0.0f)); // start from above
        lucifer->getLevel()->addObject(iceSpear);
    }
}


void LuciferVerticalBarrageState::update(Boss* boss, float dt) {


    if (timer > 0) {
        timer -= dt;
        if (timer <= 0) {
            if (rand() % 11 <= 7) {
                lucifer->getStateMachine()->changeState(LuciferIdleState::getInstance(), lucifer);
            }
            else {
                if (rand() % 2 == 0) {
                    lucifer->getStateMachine()->changeState(LuciferHorizontalBarrageState::getInstance(), lucifer);
                }
                else {
                    lucifer->getStateMachine()->changeState(LuciferVerticalBarrageState::getInstance(), lucifer);
                }
            }
        }
    }
}

void LuciferVerticalBarrageState::exit(Boss* boss) {
    //cout << "end vert barrage" << endl;
}
