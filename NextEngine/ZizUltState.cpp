#include "ZizUltState.h"

ZizUltState* ZizUltState::instance = nullptr;

ZizUltState* ZizUltState::getInstance() {
	if (!instance) {
		instance = new ZizUltState;
	}

	return instance;
}

void ZizUltState::enter(Boss* boss) {
	ziz = dynamic_cast<Ziz*>(boss);
	if (!ziz) return;


	ziz->setTexture("../Resource/Texture/FinalZiz/Zyzz_FlyUp-Sheet.png", 1, 7, 0);
	ziz->getAnimationComponent()->setState("flyup");

	

	

	hasFlew = false;
	isOffScreen = false;

	flyUpTimer = 0.08f * 7;
	activeLightning = 7.6f + 2.0f;

}

void ZizUltState::update(Boss* boss, float dt) {
	if (hasFlew == false) {
		flyUpTimer -= dt;
		if (flyUpTimer <= 0) {
			ziz->getTransform().setPosition(glm::vec3(0.0f, 9.0f, 1.0f));
			isOffScreen = true;
			if (!hasFlew) {
				hasFlew = true;
				DrawableObject* zizUltOnBg = ziz->createBGZiz();
				ziz->getLevel()->addObject(zizUltOnBg);
				ziz->startShake(0.08f * (12 * 3.75), 0.0025f);
				
			}
		}
	}
	else if (hasFlew == true) {
		activeLightning -= dt;
		if (activeLightning <= 0) {
			//qte
			ziz->getStateMachine()->changeState(ZizQTEState::getInstance(), ziz);
		}
	}
}

void ZizUltState::exit(Boss* boss) {

}