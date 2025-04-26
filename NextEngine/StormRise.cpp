#pragma once
#include "StormRise.h"

StormRise::StormRise() {
	

	setName("StormRise");
	//setTexture("../Resource/Ziz/StormRiseProjectile.png");
	getTransform().setScale(glm::vec3(3.0f, 6.0f, 1.0f));
	setDraw(true);
	//getTransform().setPosition(glm::vec3(getTransform().getPosition().x, 0.15f, 1.0f));
	addColliderComponent();
	getColliderComponent()->setTrigger(true);
	getColliderComponent()->setDimension(0.5f, 1.0f);
	setDrawCollider(true);
	initAnimation(25, 1);
	getAnimationComponent()->addState("stormtracker", 0, 25);
	getAnimationComponent()->addState("stormcaller", 0, 32);
	setTexture("../Resource/Texture/FinalZiz/VFX/StormTracker.png", 1, 25, 0);
	getAnimationComponent()->setState("stormtracker");
	

	//getColliderComponent()->setDimension(1.0f, 1.0f);
	
	canAnim = true;
	playerIsInside = false;
	hasHit = false;
	isActive = false;
	isBuffering = false;
	isRecovering = false;
	speed = 4.0f;
	damage = 10.0f;
	countdownTimer = 0.08f * 25;
	bufferTimer = 0.08f * 1;
	activeTimer = 0.08f * 26;
	recoveryTimer = 0.08f * 5;
}

void StormRise::update(float dt) {
	if (!isActive && !isBuffering) {
		countdownTimer -= dt;

		if (player) {
			
			glm::vec3 currentPosition = getTransform().getPosition();

			float playerPositionX = player->getTransform().getPosition().x;

			if (currentPosition.x < playerPositionX) {
				currentPosition.x += speed * dt;
			}
			else if (currentPosition.x > playerPositionX) {
				currentPosition.x -= speed * dt;
			}

			getTransform().setPosition(currentPosition);
		}

		if (countdownTimer <= 0.0f) {
			isBuffering = true;
			setAnimStorm();
			//cout << "buffering" << endl;
		}
	}


	// Buffer phase
	if (isBuffering == true && isActive == false) {
		bufferTimer -= dt;

		if (bufferTimer <= 0.0f) {
			//setAnimStorm();
			isBuffering = false;
			isActive = true;
		}
	}

	// Active phase
	if (isActive == true) {
		activeTimer -= dt;

		if (activeTimer < 0) {
			isRecovering = true;
			
		}
	}


	if (isRecovering == true) {
		recoveryTimer -= dt;
		//cout << "recoveryTimer : " << recoveryTimer << endl;;
		if (recoveryTimer <= 0) {
			DrawableObject::destroyObject(this);
		}
	}
}

void StormRise::setAnimStorm() {
	setTexture("../Resource/Texture/FinalZiz/VFX/StormCaller2.png", 1, 32, 0);
	getAnimationComponent()->setState("stormcaller");
}


void StormRise::onCollisionEnter(Collider* collider) {
	DrawableObject* obj = collider->getObject();
	Player* player = dynamic_cast<Player*>(obj);

	/*if (player) {
		playerIsInside = true;
		cout << "Player Entered" << endl;
	}*/
}

void StormRise::onCollisionStay(Collider* collider) {
	DrawableObject* obj = collider->getObject();
	Player* player = dynamic_cast<Player*>(obj);

	if (player) {
		//playerInside = true;

		if (player->getInvincible() || player->getIsDashing()) {
			return;
		}

		if (!hasHit) {
			if (isActive == true) {
				if (player->getShield()->getIsBlocking()) { // is blocking
					if (player->getShield()->getIsPerfect()) { //is perfectly timed
						cout << "Player perfect blocked" << endl;
						player->increaseUltimateGauge(100.0f); //instant fill
						hasHit = true;
					}
					else { //if blocking but not perfectly
						cout << "Enemy Hit Player for " << damage / 2 << " damage and " << damage / 2 << "withered damage." << endl;
						player->getHealth()->takeDamage(damage, 30);
						player->increaseUltimateGauge(damage / 2); // increase by withered damage.
						hasHit = true;
					}
				}
				else { //is not blocking
					cout << "Enemy Hit Player for " << damage << " damage." << endl;
					player->getHealth()->takeDamage(damage);
					hasHit = true;
				}
			}
			
		}

	}
	
}

void StormRise::onCollisionExit(Collider* collider){
	DrawableObject* obj = collider->getObject();
	
}

void StormRise::onTriggerEnter(Collider* collider) {

}

void StormRise::onTriggerStay(Collider* collider) {

}

void StormRise::onTriggerExit(Collider* collider) {

}

void StormRise::setPlayer(Player* playr) {
	player = playr;
}

bool StormRise::getCanAnim() {
	return canAnim;
}

