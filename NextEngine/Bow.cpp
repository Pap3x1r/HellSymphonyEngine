#include "Bow.h"
#include "Player.h"

Bow::Bow() {

}

void Bow::update(float dt, Player* player) {
	rapidShotTimeElapsed += dt;

	if (rapidShotTimeElapsed >= rapidShotTimer) {
		rapidShotReady = true;
	}

	if (isOverheat) {
		currentRapidOverheat -= overheatDecreaseRate * dt;

		if (currentRapidOverheat <= 0) {
			isOverheat = false;
			currentRapidOverheat = 0;
		}
	}
	else {
		if (currentRapidOverheat > 0) {
			currentRapidOverheat -= normalDecreaseRate * dt;
		}
		else if (currentRapidOverheat <= 0) {
			currentRapidOverheat = 0;
		}
	}

	if (currentRapidOverheat >= maxRapidOverheat) {
		isOverheat = true;
	}

	if (rapidShotDebugMode) {
		cout << currentRapidOverheat << " isOverheat? : " << isOverheat << endl;
	}
}

void Bow::setEnableDebug() {
	rapidShotDebugMode = !rapidShotDebugMode;
}

DrawableObject* Bow::arrowShot(float damage_, float ultPercentage_,Player* player, float speed) {
	glm::vec3 playerPos = player->getTransform().getPosition();
	//Create arrow
	Arrow* arrow = new Arrow(damage_, ultPercentage_, player->getFacingRight(), speed, player);
	arrow->setTexture("../Resource/Texture/arrow.png"); //set texture
	arrow->getTransform().setScale(glm::vec3(2.0f, 2.0f, 1.0f));
	if (!player->getFacingRight()) {
		arrow->getTransform().setRotationDeg(180.0f);
	}

	
	//arrow->setDraw(false);
	arrow->getTransform().setPosition(glm::vec3(playerPos.x, playerPos.y - 0.6f, playerPos.z));
	arrow->addColliderComponent();
	arrow->getColliderComponent()->setTrigger(true);
	arrow->getColliderComponent()->setEnableCollision(true); //Set collision to false at the start
	arrow->getColliderComponent()->setDimension(0.6f, 0.25f); //Set collider dimension
	//arrow->getColliderComponent()->setOffset(glm::vec3(0.0f, 0.0f, 0.0f)); //Set collider offset
	arrow->setDrawCollider(true);

	rapidShotReady = false;
	rapidShotTimeElapsed = 0.0f;
	currentRapidOverheat += overheatPerArrow;

	return arrow;
}

bool Bow::getRapidShotReady() const {
	return rapidShotReady;
}

bool Bow::getIsOverheat() const {
	return isOverheat;
}