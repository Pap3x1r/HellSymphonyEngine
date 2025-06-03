#include "Bow.h"
#include "Player.h"


Bow::Bow() {

	float scaling1 = 1.4f;
	float scaling2 = 1.75f;

	BowUltimateCollider* attack1 = new BowUltimateCollider(200, 0, 6); //Change damage and ult gain percentage here
	attack1->setName("BowSmallUlt");
	attack1->setDraw(false);
	attack1->initAnimation(0, 0);
	attack1->getAnimationComponent()->addState("smallUlt", 0, 11);
	attack1->getAnimationComponent()->setLoop(false);
	attack1->getTransform().translate(glm::vec3(0.0f, 0.35f, 0.0f));
	attack1->getTransform().setScale(glm::vec3(4.24f * scaling1, 7.2f * scaling1, 1.0f));
	attack1->addColliderComponent();
	attack1->getColliderComponent()->setTrigger(true);
	attack1->getColliderComponent()->setEnableCollision(false); //Set collision to false at the start
	attack1->setHitCooldown(0.083f * 3);
	attack1->setTimeLimit(0.083f * 11);
	attack1->getColliderComponent()->setDimension(0.625f, 1.0f); //Set collider dimension
	attack1->getColliderComponent()->getTransform().translate(glm::vec3(-0.1f, 0.0f, 0.0f));
	//attack1->getColliderComponent()->setOffset(glm::vec3(0.85f, -1.0f, 0.0f)); //Set collider offset
	attack1->setDrawCollider(false);
	chainAttackList.push_back(attack1);

	BowUltimateCollider* attack2 = new BowUltimateCollider(825, 0, 7.5f);
	attack2->setName("BowBigUlt");
	attack2->setDraw(false);
	attack2->initAnimation(0, 0);
	attack2->getAnimationComponent()->addState("bigUlt", 0, 15);
	attack2->getAnimationComponent()->setLoop(false);
	attack2->getTransform().translate(glm::vec3(0.0f, 1.0f, 0.0f));
	attack2->getTransform().setScale(glm::vec3(5.71f * scaling2, 7.2f * scaling2, 1.0f));
	attack2->addColliderComponent();
	attack2->getColliderComponent()->setTrigger(true);
	attack2->getColliderComponent()->setEnableCollision(false); //Set collision to false at the start
	attack2->setHitCooldown(0.083f * 5);
	attack2->setTimeLimit(0.083f * 15);
	attack2->getColliderComponent()->setDimension(0.425f, 0.7f); //Set collider dimension
	attack2->getColliderComponent()->getTransform().translate(glm::vec3(0.125f, 0.0f, 0.0f));
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

DrawableObject* Bow::arrowShot(float damage_, float ultPercentage_, Player* player, float speed, float overheat) {
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
	currentRapidOverheat += overheat;

	return arrow;
}

bool Bow::getRapidShotReady() const {
	return rapidShotReady;
}

bool Bow::getIsOverheat() const {
	return isOverheat;
}

void Bow::setSmallUltReady(bool v) {
	smallUltReady = v;
}

bool Bow::getSmallUltReady() const {
	return smallUltReady;
}

void Bow::setBigUltReady(bool v) {
	bigUltReady = v;
}

bool Bow::getBigUltReady() const {
	return bigUltReady;
}