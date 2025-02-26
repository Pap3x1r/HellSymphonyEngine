#pragma once
#include "StormRise.h"

StormRise::StormRise() {
	

	setName("StormRise");
	setTexture("../Resource/Ziz/StormRiseProjectile.png");
	getTransform().setScale(glm::vec3(2.5f, 2.5f, 1.0f));
	addColliderComponent();

	getColliderComponent()->setDimension(0.5f, 0.15f);
	getColliderComponent()->getTransform().translate(glm::vec3(0.0f, 0.1f, 0.0f));
	setDrawCollider(true);
	addPhysicsComponent();
	getPhysicsComponent()->setGravity(glm::vec2(0.0f, -0.02f));
	getPhysicsComponent()->setEnableGravity(true);

	playerIsInside = false;
	hasHit = false;
	isActive = false;
	speed = 5.0f;
	damage = 10.0f;
	countdownTimer = 3.0f;
	activeTimer = 2.0f;
}

StormRise::StormRise(float cdTimer) {
	playerIsInside = false;
	hasHit = false;
	isActive = false;
	speed = 5.0f;
	damage = 10.0f;
	countdownTimer = cdTimer;
	activeTimer = 2.0f;
}

void StormRise::update(float dt) {

	//cout << "Player inside: " << playerIsInside << endl;

	if (!isActive) {
		countdownTimer -= dt;
		//cout << "Counting Down: " << countdownTimer << endl;

		if (countdownTimer <= 0.0f) {
			isActive = true;
		}
	}


	if (!isActive) {
		if (player) {
			glm::vec3 playerPosition = player->getTransform().getPosition();

			glm::vec3 currentPosition = getTransform().getPosition();

			if (currentPosition.x < playerPosition.x) {
				currentPosition.x += speed * dt;
			}
			else if (currentPosition.x > playerPosition.x) {
				currentPosition.x -= speed * dt;
			}

			getTransform().setPosition(currentPosition);
		}
	}
	else if (isActive) {
		activeTimer -= dt;
		//cout << "Active Timer Countdown: " << activeTimer << endl;
		if (activeTimer <= 0.0f) {
			DrawableObject::destroyObject(this);
		}
	}

}


void StormRise::onCollisionEnter(Collider* collider) {
	DrawableObject* obj = collider->getObject();
	Player* player = dynamic_cast<Player*>(obj);

	if (player) {
		playerIsInside = true;
		cout << "Player Entered" << endl;
	}
}

void StormRise::onCollisionStay(Collider* collider) {
	/*DrawableObject* obj = collider->getObject();
	Player* player = dynamic_cast<Player*>(obj);

	if (player) {

		playerIsInside = true;
		if (!hasHit) {

			if (player->getShield()->getIsBlocking()) { // is blocking
				if (player->getShield()->getIsPerfect()) { //is perfectly timed
					cout << "Player perfect blocked" << endl;
					player->increaseUltimateGauge(100.0f); //instant fill
					hasHit = true;
				}
				else { //if blocking but not perfectly
					cout << "Enemy Hit Player for " << damage / 2 << " damage and " << damage / 2 << "withered damage." << endl;
					player->increaseUltimateGauge(damage / 2); // increase by withered damage.
					hasHit = true;
				}
			}
			else { //is not blocking
				cout << "Enemy Hit Player for " << damage << " damage." << endl;
				hasHit = true;
			}
		}

	}*/
	
}

void StormRise::onCollisionExit(Collider* collider){
	DrawableObject* obj = collider->getObject();
	Player* player = dynamic_cast<Player*>(obj);

	if (player) {
		playerIsInside = false;
		cout << "Player Exited" << endl;
	}
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

