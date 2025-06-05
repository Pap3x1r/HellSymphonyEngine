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
	delayBeforeLightning = 10.0f;

	//cout << "made zizbg" << endl;
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
	hasExited = false;
	readyToExit = false;


	startPos = getTransform().getPosition();
	endPos = glm::vec3(0.0f, 2.5f, 1.0f);

	endPos2 = glm::vec3(0.0f, 6.5f, 1.0f);
	t = 0;

	timesSummonedLightining = 2;

	startUpTimer = 0;
	startUpDuration = 0.08f * 36;
	delayBeforeLightning = 1.0f;
	delayAfterLightning = 1.0f;
	exitTimer = 0;
	exitDuration = 1.5f;
	//cout << "made zizbg" << endl;
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
			
			usedXPositions.clear();
			for (int i = 0; i < 5; i++) {
				float x = generateUniqueXPosition(-8.0f, 8.0f, 1.0f);
				DrawableObject* lightning_ = ziz->createLightning(x);
				ziz->getLevel()->addObject(lightning_);
			}

			if (timesSummonedLightining > 0) {
				timesSummonedLightining--;
				delayBeforeLightning = 1.0;
			}
			else {
				hasSummonedLightning = true;
				startPos2 = getTransform().getPosition();
				t = 0;
			}
			
			
		}
	}

	if (hasSummonedLightning == true) {
		delayAfterLightning -= dt;
		if (delayAfterLightning <= 0) {
			readyToExit = true;
		}
	}

	if (readyToExit == true) {
		exitTimer += dt;
		t = exitTimer / exitDuration;
		t = glm::clamp(t, 0.0f, 1.0f);


		// Lerp between positions
		newPos2 = glm::mix(startPos2, endPos2, t);
		getTransform().setPosition(newPos2);

		if (t >= 1.0f) {
			hasExited = true;
			
		}
	}

	if (hasExited == true) {
		DrawableObject::destroyObject(this);
	}

}

float UltZizOnBG::generateUniqueXPosition(float minX, float maxX, float step) {
	float x;
	int xKey;
	int attempts = 0;
	const int maxAttempts = 100;

	do {
		x = minX + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (maxX - minX)));
		x = std::round(x / step) * step;
		xKey = static_cast<int>(x * 100); // Scale to avoid float precision issues
		attempts++;
	} while (usedXPositions.count(xKey) > 0 && attempts < maxAttempts);

	usedXPositions.insert(xKey);
	return x;
}

