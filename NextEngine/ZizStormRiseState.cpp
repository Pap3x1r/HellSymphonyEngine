#include "ZizStormRiseState.h"
#include "ZizGroundSlamState.h"

ZizStormRiseState* ZizStormRiseState::instance = nullptr;

ZizStormRiseState* ZizStormRiseState::getInstance() {
	if (!instance) {
		instance = new ZizStormRiseState;
	}

	return instance;
}

void ZizStormRiseState::enter(Boss* boss) {
    Ziz* ziz = dynamic_cast<Ziz*>(boss);
    if (!ziz) return;

    

    
    //ziz->setTexture("../Resource/Ziz/StormRise.png");
    DrawableObject* newStormRise = ziz->createStormRise();
    ziz->setTexture("../Resource/Texture/FinalZiz/Zyzz_StormRise-Sheet.png", 1, 57, 0);
    ziz->getAnimationComponent()->setState("stormrise");


    ziz->getLevel()->addObject(newStormRise);
    ziz->facePlayer();



    
    startupTimer = 0.08f * 57;
    //recoveryTimer = startupTimer + 0.08f * 13;
}

void ZizStormRiseState::update(Boss* boss, float dt) {
    Ziz* ziz = dynamic_cast<Ziz*>(boss);
    if (!ziz) return;


    if (startupTimer > 0) {
        startupTimer -= dt;
    }
    else {
        ziz->getStateMachine()->changeState(ZizIdleState::getInstance(), ziz);
    }
    
}

void ZizStormRiseState::exit(Boss* boss) {
    //cout << "Ziz exiting StormRise State." << endl;
}