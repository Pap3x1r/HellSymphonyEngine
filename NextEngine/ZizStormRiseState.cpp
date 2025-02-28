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

    

    
    ziz->setTexture("../Resource/Ziz/StormRise.png");
    DrawableObject* newStormRise = ziz->createStormRise();
    ziz->getLevel()->addObject(newStormRise);
    ziz->facePlayer();
    std::cout << "StormRise summoned\n";
    

    std::cout << "Ziz summoned stormrise." << endl;

    timer = 0.0f;
    startupTimer = 0.08f * 24;
    recoveryTimer = startupTimer + 0.08f * 16;
}

void ZizStormRiseState::update(Boss* boss, float dt) {
    Ziz* ziz = dynamic_cast<Ziz*>(boss);
    if (!ziz) return;

    timer += dt;

    if (timer < startupTimer) {
        //std::cout << "Ziz summoned...\n";

        if (timer >= 0.08f * 8 && timer - dt < 0.08f * 8) {
            ziz->setTexture("../Resource/Ziz/StormRise_2.png");
            std::cout << "Ziz charging\n";
        }

    }
    else if (timer >= startupTimer && timer < recoveryTimer) {
        if (timer - dt < startupTimer) {  // Ensures this runs only once
            ziz->setTexture("../Resource/Ziz/WingSpan_3.png");
            std::cout << "Ziz is recovering...\n";
        }
        
    }
    else {
        std::cout << "Ziz finished recovering from the tornado.\n";
        ziz->getStateMachine()->changeState(ZizGroundSlamState::getInstance(), ziz);
    }
    
}

void ZizStormRiseState::exit(Boss* boss) {
    std::cout << "Ziz exiting StormRise State." << endl;
}