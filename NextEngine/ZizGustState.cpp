#include "ZizGustState.h"


ZizGustState* ZizGustState::instance = nullptr;

ZizGustState* ZizGustState::getInstance() {
	if (!instance) {
		instance = new ZizGustState;
	}

	return instance;
}

void ZizGustState::enter(Boss* boss) {
    Ziz* ziz = dynamic_cast<Ziz*>(boss);
    if (!ziz) return;

    timer = 0.0f;
    startupTimer = 0.08f * 8; //8 frames startup
    recoveryTimer = startupTimer + 0.08f * 10; //10 frame recovery

    ziz->setTexture("../Resource/Ziz/Gust_1.png");

    std::cout << "Ziz entered Gust State, preparing to summon a tornado.\n";
}

void ZizGustState::update(Boss* boss, float dt) {
    Ziz* ziz = dynamic_cast<Ziz*>(boss);
    if (!ziz) return;

    timer += dt;

    if (timer < startupTimer) {
        std::cout << "Ziz is preparing the tornado...\n";
    }
    else if (timer >= startupTimer && timer < recoveryTimer) {
        if (timer - dt < startupTimer) {  // Ensures this runs only once
            DrawableObject* newGust = ziz->createGust();
            ziz->getLevel()->addObject(newGust);
            std::cout << "Tornado summoned!\n";
            ziz->setTexture("../Resource/Ziz/Gust_2(V2).png");
        }
        std::cout << "Ziz is recovering...\n";
    }
    else {
        std::cout << "Ziz finished recovering from the tornado.\n";
        ziz->getStateMachine()->changeState(ZizIdleState::getInstance(), ziz);
    }
}

void ZizGustState::exit(Boss* boss) {
    std::cout << "Ziz exiting Gust State.\n";
}