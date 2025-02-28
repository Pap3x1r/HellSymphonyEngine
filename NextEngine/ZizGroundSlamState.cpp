#include "ZizGroundSlamState.h"
#include "SimpleObject.h"

ZizGroundSlamState* ZizGroundSlamState::instance = nullptr;

ZizGroundSlamState* ZizGroundSlamState::getInstance() {
	if (!instance) {
		instance = new ZizGroundSlamState();
	}

	return instance;
}

void ZizGroundSlamState::enter(Boss* boss) {
	ziz = dynamic_cast<Ziz*>(boss);
	if (!ziz) return;


	ziz->setTexture("../Resource/Ziz/Swoop_1.png");

	cout << "Entering GroundSlam" << endl;
	ziz->facePlayer();
	//ziz->getPhysicsComponent()->setEnablePhysics(false);

	player = ziz->getPlayer();
	if (player) {
		cout << "Found Player" << endl;
	}

	
	if (player) {
		if (player->getTransform().getPosition().x > 7.0f) {
			//limit ziz target to within stage
		}
		targetPos = glm::vec3(player->getTransform().getPosition().x, ziz->getTransform().getPosition().y, 0.0f);

	}

	if (abs(ziz->getTransform().getPosition().x - targetPos.x) <= 3.0f) {
		tooClose = true;
		if (abs(ziz->getTransform().getPosition().x - targetPos.x) <= 1.0f) {
			wayTooClose = true;
		}
		
	}
	endPosOffset = 2.0f;



	if (player->getTransform().getPosition().x > ziz->getTransform().getPosition().x) {
		endPos = glm::vec3(player->getTransform().getPosition().x - endPosOffset, ziz->getTransform().getPosition().y, 0.0f);
		faceDirection = -1;
	}
	else if (player->getTransform().getPosition().x < ziz->getTransform().getPosition().x) {
		endPos = glm::vec3(player->getTransform().getPosition().x + endPosOffset, ziz->getTransform().getPosition().y, 0.0f);
		faceDirection = 1;
	}
	
	cout << "EndPosOffSet: " << abs(ziz->getTransform().getPosition().x - targetPos.x) << endl;

	attackCollider = new EnemyAttackCollider(5);
	attackCollider->setDraw(false);
	attackCollider->setDrawCollider(true);
	attackCollider->addColliderComponent();
	attackCollider->setActive(false);
	attackCollider->getColliderComponent()->setTrigger(true);
	attackCollider->getColliderComponent()->setDimension(1.0f, 1.0f);
	attackCollider->getTransform().setPosition(glm::vec3(targetPos.x, player->getTransform().getPosition().y - 1.0f, 0.0f));
	ziz->getLevel()->addObject(attackCollider);

	cout << "Too Close: " << tooClose << ", way Too close: " << wayTooClose << endl;
	


	hasFlew = false;
	isAtMaxAlt = false;
	hasSlammed = false;
	isSlamming = false;

	inAirTimer = 0.08f * 6;
	slamTimer = 0;
	recoveryTimer = 0.08f * 24;


	cout << "Ziz Going to fly" << endl;
}

void ZizGroundSlamState::update(Boss * boss, float dt){
	
	if (ziz) {
		if (!hasFlew) {
			if (!isAtMaxAlt) {
				if (tooClose) {
					if (wayTooClose) {
						ziz->getTransform().translate(glm::vec3(20.0f * faceDirection * dt, 10.0f * dt, 0.0f));
					}
					else {
						ziz->getTransform().translate(glm::vec3(10.0f * faceDirection * dt, 10.0f * dt, 0.0f));
					}
					
				}
				else {
					ziz->getTransform().translate(glm::vec3(0.0f, 10.0f * dt, 0.0f));
				}
				
				if (ziz->getTransform().getPosition().y > 2.0f) {
					isAtMaxAlt = true;
					if (!hasFlew) {
						hasFlew = true;
						//cout << "Ziz flew" << endl;
						ziz->setTexture("../Resource/Ziz/GroundSlam_1.png");
						startPos = ziz->getTransform().getPosition();
					}
				}
			}
		}
		else {
			if (!isSlamming && !hasSlammed) {
				inAirTimer -= dt;
				if (inAirTimer <= 0) {
					
					ziz->setTexture("../Resource/Ziz/GroundSlam_2.png");
					cout << "Ziz gonna Slam" << endl;
					isSlamming = true;
				}
			}
			else if (isSlamming && !hasSlammed) {
				slamTimer += dt;
				t = slamTimer / slamDuration;
				t = glm::clamp(t, 0.0f, 1.0f);

				newPos = glm::mix(startPos, endPos, t);
				ziz->getTransform().setPosition(newPos);

				if (t >= 0.8f) {
					if (!attackCollider->getIsActive()) {
						attackCollider->setActive(true);
					}
				}

				if (t >= 1.0f) {
					hasSlammed = true;
					//cout << "Finished" << endl;
					ziz->setTexture("../Resource/Ziz/WingSpan_1.png");
					isSlamming = false;
					hasSlammed = true;
					//DrawableObject::destroyObject(attackCollider);
				}
			}
			else if (hasSlammed) {
				recoveryTimer -= dt;
				if (recoveryTimer <= 0) {
					//ziz->getPhysicsComponent()->setEnableGravity(true);
					ziz->getStateMachine()->changeState(ZizIdleState::getInstance(), ziz);
					DrawableObject::destroyObject(attackCollider);
				}
			}
		}
	}
}

void ZizGroundSlamState::exit(Boss* boss) {

}