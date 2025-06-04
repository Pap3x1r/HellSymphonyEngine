#include "LuciferHorizontalBarrageState.h"


LuciferHorizontalBarrageState* LuciferHorizontalBarrageState::instance = nullptr;

LuciferHorizontalBarrageState* LuciferHorizontalBarrageState::getInstance() {
    if (!instance) {
        instance = new LuciferHorizontalBarrageState();
    }
    return instance;
}

void LuciferHorizontalBarrageState::enter(Boss* boss) {
    lucifer = Lucifer::getInstance();
    timer = 3.0f;

    // Define Y positions (from bottom to top)
    std::vector<float> slotPositions = { -2.5f, -0.75f, 1.0f, 2.75f, 4.5f};

    // Choose one slot to leave empty — player's max jump height is around -0.2
    int emptyIndex = rand() % 2;
    int side = rand() % 2;

    for (int i = 0; i < slotPositions.size(); ++i) {
        if (i == emptyIndex) continue;

        // Fire spears from the left (facing right), entering screen at x = -10.0f
        if (side == 0) {
            IceSpear* iceSpear = new IceSpear(FacingDirection::right, slotPositions[i]);
            lucifer->getLevel()->addObject(iceSpear);
        }
        else {
            IceSpear* iceSpear = new IceSpear(FacingDirection::left, slotPositions[i]);
            lucifer->getLevel()->addObject(iceSpear);
        }
        
    }
}



void LuciferHorizontalBarrageState::update(Boss* boss, float dt) {


    if (timer > 0) {
        timer -= dt;
        if (timer <= 0) {
            if (rand() % 11 <= 7) {
                lucifer->getStateMachine()->changeState(LuciferIdleState::getInstance(), lucifer);
            }
            else {
                if (rand() % 2 == 0) {
                    lucifer->getStateMachine()->changeState(LuciferVerticalBarrageState::getInstance(), lucifer);
                    
                }
                else {
                    lucifer->getStateMachine()->changeState(LuciferHorizontalBarrageState::getInstance(), lucifer);
                }
            }
            
        }
    }
}

void LuciferHorizontalBarrageState::exit(Boss* boss) {
   // cout << "end vert barrage" << endl;
}
