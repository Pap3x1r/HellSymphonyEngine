#include "ZizSwoopState.h"
#include "ZizClawSlashState.h"

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

	
	
	ziz->setTexture("../Resource/Texture/FinalZiz/Zyzz_FlyUp-Sheet.png", 1, 7, 0);
	ziz->getAnimationComponent()->setState("flyup");
	//ziz->getPhysicsComponent()->setEnableGravity(false);
	isOffScreen = false;
	hasFlew = false;
	isDisplayingWarning = false;
	hasDisplayedWarning = false;
	hasReachedTarget = false;


	flyUpTimer = 0.08f * 7;
	beforeWarningTimer = 1.0f;
	recoveryTimer = 0.08f * 16;
	beforeSwoopTimer = 0.08f * 3;
	warningTimer = 2.0f + beforeSwoopTimer;
	swoopTimer = 0;

	//choose direction
	swoopDirection = (rand() % 2 == 0) ? -1 : 1;
	if (swoopDirection == -1) {
		//cout << "Ziz go from left to right" << endl;
		startPos = glm::vec3(-10.5f, 0.0f, 0.0f);
		endPos = glm::vec3(4.5f, -0.25f, 0.0f);
	}
	else if (swoopDirection == 1) {
		//cout << "Ziz go from right to left" << endl;
		startPos = glm::vec3(10.5f, 0.0f, 0.0f);
		endPos = glm::vec3(-4.5f, -0.25f, 0.0f);
	}

	newSwoopWarning = ziz->createSwoopWarning(swoopDirection);
	


	startPosUp = ziz->getTransform().getPosition();
	endPosUp = glm::vec3(ziz->getTransform().getPosition().x, ziz->getTransform().getPosition().y + 5.0f, 0.0f);


	attackCollider = new EnemyAttackCollider(7);
	attackCollider->setDraw(false);
	attackCollider->setDrawCollider(true);
	attackCollider->addColliderComponent();
	//attackCollider->setCanDrawColliderNew(true);
	attackCollider->setActive(true);
	attackCollider->getColliderComponent()->setTrigger(true);
	attackCollider->getColliderComponent()->setDimension(1.0f, 6.0f);
	attackCollider->getTransform().setPosition(glm::vec3(0.0f, -10.0f, 0.0f));

	ziz->getLevel()->addObject(attackCollider);

	SoundManager::GetInstance()->PlaySFX("Ziz_FlyUp");
	//cout << "Ziz entered swoop" << endl;
}

void ZizSwoopState::update(Boss* boss, float dt) {

	if (ziz) {
		if (!hasFlew) {
			if (!isOffScreen) {

				if (flyUpTimer > 0) {
					flyUpTimer -= dt;
				}
				else {
					ziz->getTransform().setPosition(glm::vec3(0.0f, 9.0f, 1.0f));
					isOffScreen = true;
					if (!hasFlew) {
						hasFlew = true;
					}
				}

			}

		}
		else if (hasFlew) {
			if (isOffScreen && !hasDisplayedWarning && !isDisplayingWarning) {
				beforeWarningTimer -= dt;

				//cout << "BWT: " << beforeWarningTimer << endl;
				if (beforeWarningTimer <= 0) {

					ziz->getLevel()->addObject(newSwoopWarning);
					ziz->facePlayer();
					hasDisplayedWarning = true;
					isDisplayingWarning = true;
				}

			}

			if (isOffScreen && hasDisplayedWarning && isDisplayingWarning) {
				warningTimer -= dt;
				if (warningTimer <= 0) {
					isDisplayingWarning = false;
					//cout << "Warning done" << endl;
					ziz->setTexture("../Resource/Texture/FinalZiz/Zyzz_Swoop.png", 1, 1, 0);
					ziz->getAnimationComponent()->setState("swoop");
					switch (swoopDirection) {
					case -1:
						ziz->getTransform().setPosition(glm::vec3(-10.5f, -0.25f, 0.0f));
						break;

					case 1:
						ziz->getTransform().setPosition(glm::vec3(10.5f, -0.25f, 0.0f));
						break;
					}
					ziz->facePlayer();
				}
			}

			if (isOffScreen && hasDisplayedWarning && !isDisplayingWarning) {
				if (hasReachedTarget == false) {
					swoopTimer += dt;
					//cout << "Swooping" << endl;
					// Calculate interpolation factor (0 to 1 over 0.5s)
					t = swoopTimer / swoopDuration;
					t = glm::clamp(t, 0.0f, 1.0f);


					// Lerp between positions
					newPos = glm::mix(startPos, endPos, t);
					ziz->getTransform().setPosition(newPos);
					//attack collider

					attackCollider->getTransform().setPosition(glm::vec3(ziz->getTransform().getPosition().x + (swoopDirection * -2.0f), ziz->getTransform().getPosition().y - 1.0f, 0.0f));


					// Reach player
					if (t >= 1.0f) {
						hasReachedTarget = true;
						//cout << "Finished" << endl;
						ziz->setTexture("../Resource/Texture/FinalZiz/Zyzz_Swoop_Recovery.png", 1, 16, 0);
						ziz->getAnimationComponent()->setState("swooprecovery");
						DrawableObject::destroyObject(attackCollider);
					}
				}

				if (hasReachedTarget == true) {
					recoveryTimer -= dt;
					if (recoveryTimer <= 0) {
						if (ziz->getDistanceFromPlayer() < 3.0f) {
							if ((rand() % 2) == 0){
								ziz->getStateMachine()->changeState(ZizClawSlashState::getInstance(), ziz);
							}
							else {
								ziz->getStateMachine()->changeState(ZizWingSpanState::getInstance(), ziz);
							}
							
						}
						else {
							if ((rand() % 2) == 0) {
								ziz->getStateMachine()->changeState(ZizGroundSlamState::getInstance(), ziz);
							}
							else {
								ziz->getStateMachine()->changeState(ZizIdleState::getInstance(), ziz);
							}
							
						}
						
					}
				}
			}
		}
	}
	
}

void ZizSwoopState::exit(Boss* boss) {
	//std::cout << "Ziz exiting Swoop State." << endl;
	DrawableObject::destroyObject(attackCollider);
}
