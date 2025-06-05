#include "ZizImpaleState.h"

ZizImpaleState* ZizImpaleState::instance = nullptr;

ZizImpaleState* ZizImpaleState::getInstance() {
	if (!instance) {
		instance = new ZizImpaleState;
	}

	return instance;
}

void ZizImpaleState::enter(Boss* boss) {
	ziz = Ziz::getInstance();

	/*DrawableObject* impale_ = ziz->createImpale();
	ziz->getLevel()->addObject(impale_);*/

	hasImpaled = false;
	delayBeforeImpale = 0.25f;
	timesSummonedImpale = 6;
	delayAfterImpale = 1.5f;
	poseTimer = 0.08f * 10;
	hasRecovered = false;
}

void ZizImpaleState::update(Boss* boss, float dt) {

	if (hasImpaled == false) {
		delayBeforeImpale -= dt;

		if (delayBeforeImpale <= 0) {

			DrawableObject* impale_ = ziz->createImpale();
			ziz->getLevel()->addObject(impale_);
			//cout << "summonlighting" << endl;

			if (timesSummonedImpale > 0) {
				timesSummonedImpale--;
				delayBeforeImpale = 0.25f;
			}
			else {
				hasImpaled = true;
				ziz->setTexture("../Resource/Texture/FinalZiz/QTE/qtestart3.png", 1, 10, 0);
				ziz->getAnimationComponent()->setState("qterecovery");
			}
		}
	}
	else {
		if (ziz->getTransform().getPosition().y >= 8.0) {
			delayAfterImpale -= dt;
			if (delayAfterImpale <= 0) {
				ziz->getTransform().setPosition(glm::vec3(6.0f, ziz->getTransform().getPosition().y, 0));
				ziz->facePlayer();
				ziz->getStateMachine()->changeState(ZizGroundSlamState::getInstance(), ziz);
			}
		}
		else {
			if (hasRecovered == false) {
				if (poseTimer > 0) {
					poseTimer -= dt;
					if (poseTimer <= 0) {
						ziz->facePlayer();
						ziz->getStateMachine()->changeState(ZizGroundSlamState::getInstance(), ziz);
					}
				}

			}
		}


		
	}
	
}

void ZizImpaleState::exit(Boss* boss) {

}