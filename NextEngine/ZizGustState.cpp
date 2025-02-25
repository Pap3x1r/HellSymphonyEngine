#include "ZizGustState.h"
#include "Ziz.h"
#include "Gust.h"

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

    //look at player
	//ziz->getStateMachine()->changeState(ZizGustState::getInstance(), ziz);
    //ziz->getAnimationComponent()->setState("gust");

	gustTimer = 0.0f;
	gustWaitTime = 0.08f * 8; // 8 frames for startup

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
    else if (gustTimer < gustWaitTime + 0.08f) {
        // Active phase - Summon the tornado
        std::cout << "Tornado summoned!\n";
        //Gust* gust = new Gust(ziz);  // Create a new tornado instance
        //ziz->getLevel()->addObject(gust);  // Add it to the level or objects list

        // Transition back to idle after tornado is summoned
        ziz->getStateMachine()->changeState(ZizIdleState::getInstance(), ziz);
    }
}

void ZizGustState::exit(Boss* boss) {
    std::cout << "Ziz exiting Gust State.\n";
}