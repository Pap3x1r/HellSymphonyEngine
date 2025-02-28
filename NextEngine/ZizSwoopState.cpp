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

	
	ziz->setTexture("../Resource/Ziz/Swoop_1.png");
	//ziz->getPhysicsComponent()->setEnableGravity(false);
	isOffScreen = false;
	hasFlew = false;
	isDisplayingWarning = false;
	hasDisplayedWarning = false;
	hasReachedTarget = false;

	beforeWarningTimer = 1.0f;
	recoveryTimer = 0.08f * 8;
	beforeSwoopTimer = 0.08f * 3;
	warningTimer = 2.0f + beforeSwoopTimer;
	swoopTimer = 0;

	//choose direction
	swoopDirection = (rand() % 2 == 0) ? -1 : 1;
	if (swoopDirection == -1) {
		cout << "Ziz go from left to right" << endl;
		startPos = glm::vec3(-10.5f, 0.0f, 0.0f);
		endPos = glm::vec3(4.5f, 0.0f, 0.0f);
	}
	else if (swoopDirection == 1) {
		cout << "Ziz go from right to left" << endl;
		startPos = glm::vec3(10.5f, 0.0f, 0.0f);
		endPos = glm::vec3(-4.5f, 0.0f, 0.0f);
	}

	newSwoopWarning = ziz->createSwoopWarning(swoopDirection);
	


	startPosUp = ziz->getTransform().getPosition();
	endPosUp = glm::vec3(ziz->getTransform().getPosition().x, ziz->getTransform().getPosition().y + 5.0f, 0.0f);


	attackCollider = new EnemyAttackCollider(5);
	attackCollider->setDraw(false);
	attackCollider->setDrawCollider(true);
	attackCollider->addColliderComponent();
	attackCollider->setActive(true);
	attackCollider->getColliderComponent()->setTrigger(true);
	attackCollider->getColliderComponent()->setDimension(1.0f, 3.0f);
	attackCollider->getTransform().setPosition(glm::vec3(0.0f,-10.0f,0.0f));
	
	ziz->getLevel()->addObject(attackCollider);

	cout << "Ziz entered swoop" << endl;
}

void ZizSwoopState::update(Boss* boss, float dt) {
	
	if (ziz) {
		if (!hasFlew) {
			if (!isOffScreen) {
				ziz->getTransform().translate(glm::vec3(0.0f, 20.0f * dt, 0.0f));
				if (ziz->getTransform().getPosition().y > 9.0f) {
					isOffScreen = true;
					if (!hasFlew) {
						hasFlew = true;
						//cout << "Ziz flew" << endl;


					}
				}
			}
			
		}
		else if (hasFlew){
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
					ziz->setTexture("../Resource/Ziz/Swoop_2 v2.png");
					switch (swoopDirection) {
					case -1:
						ziz->getTransform().setPosition(glm::vec3(-10.5f, 0.0f, 0.0f));
						break;

					case 1:
						ziz->getTransform().setPosition(glm::vec3(10.5f, 0.0f, 0.0f));
						break;
					}
					ziz->facePlayer();
				}
			}

			if (isOffScreen && hasDisplayedWarning && !isDisplayingWarning) {
				if (!hasReachedTarget) {
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
						ziz->setTexture("../Resource/Ziz/Swoop_3.png");
						DrawableObject::destroyObject(attackCollider);
					}
				}
				else {
					recoveryTimer -= dt;
					if (recoveryTimer <= 0) {
						//ziz->getPhysicsComponent()->setEnableGravity(true);
						DrawableObject::destroyObject(attackCollider);
						ziz->getStateMachine()->changeState(ZizClawSlashState::getInstance(), ziz);
					}
				}
			}
		}
	}
	
}

void ZizSwoopState::exit(Boss* boss) {
	std::cout << "Ziz exiting Swoop State." << endl;
}
