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



    idleTimer = 0.08f * 10;

    //ziz->setTexture("../Resource/Texture/FinalZiz/Zyzz_Idle-Sheet.png", 1, 10, 0);
    //ziz->getAnimationComponent()->setState("idle");

}

void LuciferIdleState::update(Boss* boss, float dt) {

    if (idleTimer > 0) {
        idleTimer -= dt;
    }
    else {
        //ziz->getStateMachine()->changeState(ZizStormRiseState::getInstance(), ziz);
        //ziz->getStateMachine()->changeState(ZizIdleState::getInstance(), ziz);
        //pickState();
    }
}

void LuciferIdleState::exit(Boss* boss) {
    //cout << "Ziz exiting Idle State.\n";
}

void LuciferIdleState::pickState() {
    float randValue = (rand() % 11);
    cout << "Rand In Idle: " << randValue << endl;


    


}
