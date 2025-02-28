#include "ZizSwoopState.h"

ZizSwoopState* ZizSwoopState::instance = nullptr;

ZizSwoopState* ZizSwoopState::getInstance() {
	if (!instance) {
		instance = new ZizSwoopState;
	}

	return instance;
}

void ZizSwoopState::enter(Boss* boss) {
	ziz = dynamic_cast<Ziz*>(boss);
	if (!ziz) return;

	
	ziz->setTexture("../Resource/Ziz/Swoop_1.png");
	ziz->getPhysicsComponent()->setEnableGravity(false);
	isOffScreen = false;
	hasFlew = false;
	isDisplayingWarning = false;
	hasDisplayedWarning = false;

	swoopDirection = (rand() % 2 == 0) ? -1 : 1;
	cout << "Ziz entered swoop" << endl;
}

void ZizSwoopState::update(Boss* boss, float dt) {
	if (ziz) {
		if (!hasFlew) {
			if (!isOffScreen) {
				ziz->getTransform().translate(glm::vec3(0.0f, 0.005f, 0.0f));
				if (ziz->getTransform().getPosition().y > 9.0f) {
					isOffScreen = true;
					cout << "Ziz flew" << endl;
					if (!hasFlew) {
						hasFlew = true;
						switch (swoopDirection) {
							case -1:
								ziz->getTransform().setPosition(glm::vec3(-10.5f, 0.0f, 0.0f));
								break;

							case 1:
								ziz->getTransform().setPosition(glm::vec3(10.5f, 0.0f, 0.0f));
								break;
						}

						

						
					}
				}
			}
			
		}
		else if (hasFlew){
			if (isOffScreen && !hasDisplayedWarning && !isDisplayingWarning) {
				beforeWarningTimer -= dt;
				//cout << "BWT: " << beforeWarningTimer << endl;
				if (beforeWarningTimer <= 0) {
					DrawableObject* newSwoopWarning = ziz->createSwoopWarning(swoopDirection);
					ziz->getLevel()->addObject(newSwoopWarning);
					ziz->facePlayer();
					isDisplayingWarning = true;
					hasDisplayedWarning = true;
				}
			}
		}
	}
	
}

void ZizSwoopState::exit(Boss* boss) {

}
