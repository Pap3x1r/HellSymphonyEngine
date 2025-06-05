#include "ZizClawSlashState.h"

ZizClawSlashState* ZizClawSlashState::instance = nullptr;

ZizClawSlashState* ZizClawSlashState::getInstance() {
	if (!instance) {
		instance = new ZizClawSlashState;
	}

	return instance;
}

void ZizClawSlashState::enter(Boss* boss) {
	ziz = dynamic_cast<Ziz*>(boss);
	if (ziz) {
		//cout << "Found Ziz" << endl;
	}

	ziz->setTexture("../Resource/Texture/FinalZiz/clawslash/1_1_Zyzz_ClawSlash_Startup_1.png", 1, 16, 0);
	ziz->getAnimationComponent()->setState("clawslashstartup1");


	findPlayer();

    slashCount = 0;
    isSlashing = false;
    hasSlashed = false;
    isPreparing = false;
    isStartingUp = true;

    attackOffSet = 3.0f;

    startUpTimer = 0.08f * 10;

    startUpTimer1 = 0.08f * 6;
    activeTimer1 = 0.08f * 4;
    pauseTimer1 = 0.08f * 0;

    startUpTimer2 = 0.08f * 2;
    activeTimer2 = 0.08f * 3;
    pauseTimer2 = 0.08f * 0;

    startUpTimer3 = 0.08f * 4;
    activeTimer3 = 0.08f * 6;
    pauseTimer3 = 0.08f * 0;

    recoveryTimer = 0.08f * 9;

	attackCollider1 = new EnemyAttackCollider(5);
	attackCollider1->setDraw(false);
	attackCollider1->setDrawCollider(true);
	//attackCollider1->setCanDrawColliderNew(true);
	attackCollider1->addColliderComponent();
	attackCollider1->setActive(false);
	attackCollider1->getColliderComponent()->setTrigger(true);
	attackCollider1->getColliderComponent()->setDimension(1.0f, 3.0f);
	attackCollider1->getTransform().setPosition(glm::vec3(ziz->getTransform().getPosition().x + attackOffSet, ziz->getTransform().getPosition().y - 1.5f, 0.0f));

	attackCollider2 = new EnemyAttackCollider(5);
	attackCollider2->setDraw(false);
	attackCollider2->setDrawCollider(true);
	//attackCollider2->setCanDrawColliderNew(true);
	attackCollider2->addColliderComponent();
	attackCollider2->setActive(false);
	attackCollider2->getColliderComponent()->setTrigger(true);
	attackCollider2->getColliderComponent()->setDimension(1.0f, 3.0f);
	attackCollider2->getTransform().setPosition(glm::vec3(ziz->getTransform().getPosition().x + attackOffSet, ziz->getTransform().getPosition().y - 1.5f, 0.0f));

	attackCollider3 = new EnemyAttackCollider(5);
	attackCollider3->setDraw(false);
	attackCollider3->setDrawCollider(true);
	//attackCollider3->setCanDrawColliderNew(true);
	attackCollider3->addColliderComponent();
	attackCollider3->setActive(false);
	attackCollider3->getColliderComponent()->setTrigger(true);
	attackCollider3->getColliderComponent()->setDimension(3.0f, 3.0f);
	attackCollider3->getTransform().setPosition(glm::vec3(ziz->getTransform().getPosition().x + attackOffSet, ziz->getTransform().getPosition().y - 1.5f, 0.0f));

	//cout << "Ziz Ready to ClawSlash" << endl;
	SoundManager::GetInstance()->PlaySFX("Ziz_ClawSlash");
}

void ZizClawSlashState::update(Boss* boss, float dt) {

	if (slashCount < 3) {

		if (isStartingUp) {
			startUpTimer -= dt;
			if (startUpTimer <= 0) {
				isPreparing = true;
				isStartingUp = false;
				//ziz->setTexture("../Resource/Ziz/ClawSlash_4.png");
			}
		}
		
		if (isPreparing && !isSlashing && !hasSlashed) {

			switch (slashCount) {
				case 0:
					startUpTimer1 -= dt;
					ziz->getTransform().translate(glm::vec3(-5.0f * facingDirection * dt, 0.0f, 0.0f));
					if (startUpTimer1 <= 0) {
						isPreparing = false;
						isSlashing = true;
						//cout << "About to Slash" << endl;
						//ziz->setTexture("../Resource/Ziz/ClawSlash_1.png");
						ziz->getLevel()->addObject(attackCollider1);
						attackCollider1->setActive(true);
						ziz->setTexture("../Resource/Texture/FinalZiz/clawslash/1_2_Zyzz_ClawSlash_Active_1.png", 1, 4, 0);
						ziz->getAnimationComponent()->setState("clawslashactive1");
					}
					break;
				case 1:
					startUpTimer2 -= dt;
					ziz->getTransform().translate(glm::vec3(-5.0f * facingDirection * dt, 0.0f, 0.0f));
					if (startUpTimer2 <= 0) {
						isPreparing = false;
						isSlashing = true;
						//cout << "About to Slash" << endl;
						//ziz->setTexture("../Resource/Ziz/ClawSlash_2.png");
						ziz->getLevel()->addObject(attackCollider2);
						attackCollider2->setActive(true);
						ziz->setTexture("../Resource/Texture/FinalZiz/clawslash/2_2_Zyzz_ClawSlash_Active_2.png", 1, 3, 0);
						ziz->getAnimationComponent()->setState("clawslashactive2");
					}
					break;
				case 2:
					startUpTimer3 -= dt;
					ziz->getTransform().translate(glm::vec3(-5.0f * facingDirection * dt, 0.0f, 0.0f));
					if (startUpTimer3 <= 0) {
						isPreparing = false;
						isSlashing = true;
						//cout << "About to Slash" << endl;
						//ziz->setTexture("../Resource/Ziz/ClawSlash_3.png");
						ziz->getLevel()->addObject(attackCollider3);
						attackCollider3->setActive(true);
						ziz->setTexture("../Resource/Texture/FinalZiz/clawslash/3_2_Zyzz_ClawSlash_Active_3.png", 1, 6, 0);
						ziz->getAnimationComponent()->setState("clawslashactive3");
					}
					break;
			}
			

		}
		else if (!isPreparing && isSlashing && !hasSlashed) {
			switch (slashCount) {
				case 0:
					activeTimer1 -= dt;
					ziz->getTransform().translate(glm::vec3(15.0f * facingDirection * dt, 0.0f, 0.0f));
					
					attackCollider1->getTransform().setPosition(glm::vec3(ziz->getTransform().getPosition().x + (attackOffSet * facingDirection), ziz->getTransform().getPosition().y - 1.5f,0.0f));
					if (activeTimer1 <= 0) {
						isSlashing = false;
						hasSlashed = true;
						//cout << "finish slashing" << endl;
						DrawableObject::destroyObject(attackCollider1);
						ziz->setTexture("../Resource/Texture/FinalZiz/clawslash/2_1_Zyzz_ClawSlash_Startup_2.png", 1, 2, 0);
						ziz->getAnimationComponent()->setState("clawslashstartup2");
					}
					break;
				case 1:
					activeTimer2 -= dt;
					ziz->getTransform().translate(glm::vec3(15.0f * facingDirection * dt, 0.0f, 0.0f));
					
					attackCollider2->getTransform().setPosition(glm::vec3(ziz->getTransform().getPosition().x + (attackOffSet * facingDirection), ziz->getTransform().getPosition().y - 1.5f, 0.0f));
					if (activeTimer2 <= 0) {
						isSlashing = false;
						hasSlashed = true;
						//cout << "finish slashing" << endl;
						DrawableObject::destroyObject(attackCollider2);
						ziz->setTexture("../Resource/Texture/FinalZiz/clawslash/3_1_Zyzz_ClawSlash_Startup_3.png", 1, 4, 0);
						ziz->getAnimationComponent()->setState("clawslashstartup3");
					}
					break;
				case 2:
					activeTimer3 -= dt;
					ziz->getTransform().translate(glm::vec3(10.0f * facingDirection * dt, 0.0f, 0.0f));
					attackCollider3->getTransform().setPosition(glm::vec3(ziz->getTransform().getPosition().x + (attackOffSet * facingDirection), ziz->getTransform().getPosition().y - 1.5f, 0.0f));
					if (activeTimer3 <= 0) {
						isSlashing = false;
						hasSlashed = true;
						//cout << "finish slashing" << endl;
						DrawableObject::destroyObject(attackCollider3);
						ziz->setTexture("../Resource/Texture/FinalZiz/clawslash/4_Zyzz_ClawSlash_Recovery.png", 1, 9, 0);
						ziz->getAnimationComponent()->setState("clawslashrecovery");
					}
					break;
			}
		}
		else if (!isPreparing && !isSlashing && hasSlashed) {

			switch (slashCount) {
			case 0:
				pauseTimer1 -= dt;

				if (pauseTimer1 <= 0) {
					isPreparing = true;
					hasSlashed = false;
					//ziz->setTexture("../Resource/Ziz/ClawSlash_4.png");
					slashCount++;
					findPlayer();
				}
				break;
			case 1:
				pauseTimer2 -= dt;

				if (pauseTimer2 <= 0) {
					isPreparing = true;
					hasSlashed = false;
					//ziz->setTexture("../Resource/Ziz/ClawSlash_4.png");
					slashCount++;
					findPlayer();
				}
				break;
			case 2:
				pauseTimer3 -= dt;

				if (pauseTimer3 <= 0) {
					isPreparing = true;
					hasSlashed = false;
					//ziz->setTexture("../Resource/Ziz/ClawSlash_4.png");
					slashCount++;
				}
				break;
			}
			
		}

	}
	else {
		// **Recovery Phase**
		recoveryTimer -= dt;
		//cout << "recovering" << endl;
		if (recoveryTimer <= 0) {
			if (ziz->getDistanceFromPlayer() < 3.0f) {
				if ((rand() % 2) == 0) {
					ziz->getStateMachine()->changeState(ZizIdleState::getInstance(), ziz);
				}
				else {
					ziz->getStateMachine()->changeState(ZizWingSpanState::getInstance(), ziz);
				}

			}
			else {
				ziz->getStateMachine()->changeState(ZizIdleState::getInstance(), ziz);
			}
		}
	}


}

void ZizClawSlashState::exit(Boss* boss) {
	DrawableObject::destroyObject(attackCollider1);
	DrawableObject::destroyObject(attackCollider2);
	DrawableObject::destroyObject(attackCollider3);
}

void ZizClawSlashState::findPlayer() {
	ziz->facePlayer();
	if (ziz->getFacingRight()) {
		facingDirection = 1;
	}
	else {
		facingDirection = -1;
	}
}