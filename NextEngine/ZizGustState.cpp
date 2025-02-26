#include "ZizGustState.h"
#include "Ziz.h"
#include "Gust.h"
#include "Level.h"

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

    gustTimer = 0.0f;
    gustWaitTime = 0.08f * 8;       // 8 frames for startup
    gustRecoveryTime = gustWaitTime + 0.08f * 10;  // 10 frames after launch

    ziz->setTexture("../Resource/Ziz/Gust_1.png");

    std::cout << "Ziz entered Gust State, preparing to summon a tornado.\n";
}

void ZizGustState::update(Boss* boss, float dt) {
    Ziz* ziz = dynamic_cast<Ziz*>(boss);
    if (!ziz) return;

    gustTimer += dt;

    if (gustTimer < gustWaitTime) {
        // Startup phase - Ziz is preparing the tornado
        std::cout << "Ziz is preparing the tornado...\n";
    }
    else if (gustTimer >= gustWaitTime && gustTimer < gustRecoveryTime) {
        // Active phase - Summon the tornado (only happens once)
        if (gustTimer - dt < gustWaitTime) {  // Ensures this runs only once
            DrawableObject* newGust = ziz->createGust();
            ziz->getLevel()->addObject(newGust);
            std::cout << "Tornado summoned!\n";
            ziz->setTexture("../Resource/Ziz/Gust_2.png");
        }
        // Recovery phase - Ziz pauses before transitioning
        std::cout << "Ziz is recovering...\n";
    }
    else {
        // Recovery phase over - return to idle
        std::cout << "Ziz finished recovering from the tornado.\n";
        ziz->getStateMachine()->changeState(ZizIdleState::getInstance(), ziz);
    }
}

void ZizGustState::exit(Boss* boss) {
    std::cout << "Ziz exiting Gust State.\n";
}