#include "UltZizOnBG.h"

UltZizOnBG::UltZizOnBG() {
	setTexture("../Resource/Texture/FinalZiz/QTE/Zyzz on BG/Zyzz_QTE_BG_Phase1.png");


	getTransform().setScale(glm::vec3(5.0f, 5.0f, 1.0f));
	getTransform().setPosition(glm::vec3(0.0f, 6.0f, 0.0f));


	enteredScreen = false;


	startPos = getTransform().getPosition();
	endPos = glm::vec3(0.0f, 2.5f, 1.0f);
	t = 0;

	startUpTimer = 0;
	startUpDuration = 0.08f * 36;
	delayBeforeLightning = 0.08f * 12;

	cout << "made zizbg" << endl;
}

UltZizOnBG::UltZizOnBG(Ziz* boss) {
	ziz = dynamic_cast<Ziz*>(boss);
	if (ziz) {
		//cout << "Found Ziz in Lightning" << endl;
	}


	setTexture("../Resource/Texture/FinalZiz/QTE/Zyzz on BG/Zyzz_QTE_BG_Phase1.png");


	getTransform().setScale(glm::vec3(5.0f, 5.0f, 1.0f));
	getTransform().setPosition(glm::vec3(0.0f, 6.0f, 0.0f));


	enteredScreen = false;
	hasSummonedLightning = false;


	startPos = getTransform().getPosition();
	endPos = glm::vec3(0.0f, 2.5f, 1.0f);
	t = 0;

	startUpTimer = 0;
	startUpDuration = 0.08f * 36;
	delayBeforeLightning = 0.08f * 12;
	cout << "made zizbg" << endl;
}



void UltZizOnBG::update(float dt) {

	if (enteredScreen == false) {
		startUpTimer += dt;
		t = startUpTimer / startUpDuration;
		t = glm::clamp(t, 0.0f, 1.0f);


		// Lerp between positions
		newPos = glm::mix(startPos, endPos, t);
		getTransform().setPosition(newPos);

		if (t >= 1.0f) {
			enteredScreen = true;
		}
	}

	if (enteredScreen == true && hasSummonedLightning == false) {
		delayBeforeLightning -= dt;
		if (delayBeforeLightning <= 0) {

			for (int i = 0; i < 3; i++) {
				DrawableObject* lightning_ = ziz->createLightning();
				ziz->getLevel()->addObject(lightning_);
			}
			
			hasSummonedLightning = true;
		}
	}


}