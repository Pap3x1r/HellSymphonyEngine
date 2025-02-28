#include "Bow.h"
#include "Player.h"

Bow::Bow() {
	BowUltimateCollider* attack1 = new BowUltimateCollider(50, 0, 5); //Change damage and ult gain percentage here
	attack1->setName("BowSmallUlt");
	attack1->setDraw(false);
	attack1->addColliderComponent();
	attack1->getColliderComponent()->setTrigger(true);
	attack1->getColliderComponent()->setEnableCollision(false); //Set collision to false at the start
	attack1->getColliderComponent()->setDimension(3.0f, 9.0f); //Set collider dimension
	//attack1->getColliderComponent()->setOffset(glm::vec3(0.85f, -1.0f, 0.0f)); //Set collider offset
	attack1->setDrawCollider(false);
	chainAttackList.push_back(attack1);

	BowUltimateCollider* attack2 = new BowUltimateCollider(100, 0, 6.5);
	attack2->setName("BowBigUlt");
	attack2->setDraw(false);
	attack2->addColliderComponent();
	attack2->getColliderComponent()->setTrigger(true);
	attack2->getColliderComponent()->setEnableCollision(false); //Set collision to false at the start
	attack2->getColliderComponent()->setDimension(5.0f, 9.0f); //Set collider dimension
	//attack2->getColliderComponent()->setOffset(glm::vec3(1.55f, -1.0f, 0.0f)); //Set collider offset
	attack2->setDrawCollider(false);
	chainAttackList.push_back(attack2);
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