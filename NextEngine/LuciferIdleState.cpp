#include "LuciferIdleState.h"
#include "Lucifer.h"

LuciferIdleState* LuciferIdleState::instance = nullptr;

LuciferIdleState* LuciferIdleState::getInstance() {
    if (!instance) {
        instance = new LuciferIdleState();
    }
    return instance;
}

void LuciferIdleState::enter(Boss* boss) {
    lucifer = Lucifer::getInstance();
    player = lucifer->getPlayer();
    luciferHeartBeat = LuciferHeartBeat::getInstance();
    


    idleTimer = 0.08f * 12;

    //cout << "Lucifer Idle Enter" << endl;
}

void LuciferIdleState::update(Boss* boss, float dt) {

    if (idleTimer > 0) {
        idleTimer -= dt;
    }
    else {
        //lucifer->getStateMachine()->changeState(LuciferBeamRadiantState::getInstance(), lucifer);
        //lucifer->getStateMachine()->changeState(LuciferIdleState::getInstance(), lucifer);
        pickState();
    }
}

void LuciferIdleState::exit(Boss* boss) {
    
}

void LuciferIdleState::pickState() {
    //lucifer has 7 moves
    int randValue = (rand() % 8);
    //cout << "Rand In Idle: " << randValue << endl;
    switch (randValue) {
    case 0:
        lucifer->getStateMachine()->changeState(LuciferBeamRadiantState::getInstance(), lucifer);
        break;
    case 1:
        lucifer->getStateMachine()->changeState(LuciferHomingSpearState::getInstance(), lucifer);
        break;
    case 2:
        lucifer->getStateMachine()->changeState(LuciferHorizontalBarrageState::getInstance(), lucifer);
        break;
    case 3:
        lucifer->getStateMachine()->changeState(LuciferVerticalBarrageState::getInstance(), lucifer);
        break;
    case 4:
        lucifer->getStateMachine()->changeState(LuciferIceFloorState::getInstance(), lucifer);
        break;
    case 5:
        lucifer->getStateMachine()->changeState(LuciferIceBombState::getInstance(), lucifer);
        break;
    case 6:
        lucifer->getStateMachine()->changeState(LuciferQTEState::getInstance(), lucifer);
        break;
    default:
        break;
    }

}
