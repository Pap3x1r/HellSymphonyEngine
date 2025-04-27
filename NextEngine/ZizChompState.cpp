#include "ZizChompState.h"

ZizChompState* ZizChompState::instance = nullptr;

ZizChompState* ZizChompState::getInstance() {
	if (!instance) {
		instance = new ZizChompState;
	}

	return instance;
}

void ZizChompState::enter(Boss* boss) {
	ziz = dynamic_cast<Ziz*>(boss);
	if (ziz) {
		//cout << "Found Ziz" << endl;
	}
	//ziz->setTexture("../Resource/Ziz/Gust_2.png");
	ziz->setTexture("../Resource/Texture/FinalZiz/Zyzz_Chomp/Zyzz_Chomp-Sheet.png", 1, 32, 0);
	ziz->getAnimationComponent()->setState("chomp");
	findPlayer();

	chompCount = 0;
	isChomping = false;
	hasChomped = false;
	isPreparing = false;
	isStartingUp = true;

	attackOffSet1 = 2.25f;
	attackOffSet2 = 5.0f;

	startUpTimer = 0.08f * 0;

	startUpTimer1 = 0.08f * 10;
	activeTimer1 = 0.08f * 2;
	pauseTimer1 = 0.08f * 0;

	startUpTimer2 = 0.08f * 4;
	activeTimer2 = 0.08f * 2;
	pauseTimer2 = 0.08f * 0;

	recoveryTimer = 0.08f * 14;

	attackCollider1 = new EnemyAttackCollider(5);
	attackCollider1->setDraw(false);
	attackCollider1->setDrawCollider(true);
	attackCollider1->addColliderComponent();
	attackCollider1->setActive(false);
	attackCollider1->getColliderComponent()->setTrigger(true);
	attackCollider1->getColliderComponent()->setDimension(1.0f, 3.0f);
	attackCollider1->getTransform().setPosition(glm::vec3(ziz->getTransform().getPosition().x + attackOffSet1, ziz->getTransform().getPosition().y - 1.5f, 0.0f));

	attackCollider2 = new EnemyAttackCollider(5);
	attackCollider2->setDraw(false);
	attackCollider2->setDrawCollider(true);
	attackCollider2->addColliderComponent();
	attackCollider2->setActive(false);
	attackCollider2->getColliderComponent()->setTrigger(true);
	attackCollider2->getColliderComponent()->setDimension(1.0f, 3.0f);
	attackCollider2->getTransform().setPosition(glm::vec3(ziz->getTransform().getPosition().x + attackOffSet2, ziz->getTransform().getPosition().y - 1.5f, 0.0f));

	//cout << "Ziz Ready to ClawSlash" << endl;
	/*if (ziz->getFacingRight() == false) {
		ziz->getTransform().setPosition(glm::vec3(ziz->getTransform().getPosition().x - 1.6f, ziz->getTransform().getPosition().y, ziz->getTransform().getPosition().z));
	}
	else {
		ziz->getTransform().setPosition(glm::vec3(ziz->getTransform().getPosition().x + 1.6f, ziz->getTransform().getPosition().y, ziz->getTransform().getPosition().z));
	}*/

}

void ZizChompState::update(Boss* boss, float dt) {



	if (chompCount < 2) {

		if (isStartingUp) {
			startUpTimer -= dt;
			if (startUpTimer <= 0) {
				isPreparing = true;
				isStartingUp = false;
				//ziz->setTexture("../Resource/Ziz/ClawSlash_4.png");
			}
		}

		if (isPreparing && !isChomping && !hasChomped) { //preparing to chomp

			switch (chompCount) {
			case 0:
				startUpTimer1 -= dt;

				//ziz->getTransform().translate(glm::vec3(-5.0f * facingDirection * dt, 0.0f, 0.0f));
				if (startUpTimer1 <= 0) {
					isPreparing = false;
					isChomping = true;
					//cout << "About to Slash" << endl;
					//ziz->setTexture("../Resource/Ziz/ClawSlash_1.png");
					ziz->getLevel()->addObject(attackCollider1);
					attackCollider1->setActive(true);
				}
				break;
			case 1:
				startUpTimer2 -= dt;

				//ziz->getTransform().translate(glm::vec3(-5.0f * facingDirection * dt, 0.0f, 0.0f));
				if (startUpTimer2 <= 0) {
					isPreparing = false;
					isChomping = true;
					//cout << "About to Slash" << endl;
					//ziz->setTexture("../Resource/Ziz/ClawSlash_2.png");
					ziz->getLevel()->addObject(attackCollider2);
					attackCollider2->setActive(true);
				}
				break;
			}


		}
		else if (!isPreparing && isChomping && !hasChomped) { //is chomping
			switch (chompCount) {
			case 0:
				activeTimer1 -= dt;

				//ziz->getTransform().translate(glm::vec3(25.0f * facingDirection * dt, 0.0f, 0.0f));
				attackCollider1->getTransform().setPosition(glm::vec3(ziz->getTransform().getPosition().x + (attackOffSet1 * facingDirection), ziz->getTransform().getPosition().y - 1.5f, 0.0f));
				if (activeTimer1 <= 0) {
					isChomping = false;
					hasChomped = true;
					//cout << "finish slashing" << endl;
					DrawableObject::destroyObject(attackCollider1);
				}
				break;
			case 1:
				activeTimer2 -= dt;

				//ziz->getTransform().translate(glm::vec3(25.0f * facingDirection * dt, 0.0f, 0.0f));
				attackCollider2->getTransform().setPosition(glm::vec3(ziz->getTransform().getPosition().x + (attackOffSet2 * facingDirection), ziz->getTransform().getPosition().y - 1.5f, 0.0f));
				if (activeTimer2 <= 0) {
					isChomping = false;
					hasChomped = true;
					//cout << "finish slashing" << endl;
					DrawableObject::destroyObject(attackCollider2);
				}
				break;
			}
		}
		else if (!isPreparing && !isChomping && hasChomped) {

			switch (chompCount) {
			case 0:
				pauseTimer1 -= dt;

				if (pauseTimer1 <= 0) {
					isPreparing = true;
					hasChomped = false;
					//ziz->setTexture("../Resource/Ziz/ClawSlash_4.png");
					chompCount++;
					//findPlayer();
				}
				break;
			case 1:
				pauseTimer2 -= dt;

				if (pauseTimer2 <= 0) {
					isPreparing = true;
					hasChomped = false;
					//ziz->setTexture("../Resource/Ziz/ClawSlash_4.png");
					chompCount++;
					//findPlayer();
				}
				break;
			}

		}

	}
	else {
		// **Recovery Phase**
		recoveryTimer -= dt;
		if (recoveryTimer <= 0) {
			/*if (ziz->getFacingRight() == false) {
				ziz->getTransform().setPosition(glm::vec3(ziz->getTransform().getPosition().x + 1.6f, ziz->getTransform().getPosition().y, ziz->getTransform().getPosition().z));
			}
			else {
				ziz->getTransform().setPosition(glm::vec3(ziz->getTransform().getPosition().x - 1.6f, ziz->getTransform().getPosition().y, ziz->getTransform().getPosition().z));
			}*/
				
			ziz->getStateMachine()->changeState(ZizIdleState::getInstance(), ziz);
		}
	}


}

void ZizChompState::exit(Boss* boss) {

}

void ZizChompState::findPlayer() {
	ziz->facePlayer();
	if (ziz->getFacingRight()) {
		facingDirection = 1;
	}
	else {
		facingDirection = -1;
	}
}