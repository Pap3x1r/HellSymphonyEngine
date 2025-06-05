#include "Shield.h"

Shield::Shield() {
	PlayerAttackCollider* attack1 = new PlayerAttackCollider(80, 25); //Change damage and ult gain percentage here
	attack1->setName("Attack1");
	attack1->setDraw(false);
	attack1->addColliderComponent();
	attack1->getColliderComponent()->setTrigger(true);
	attack1->getColliderComponent()->setEnableCollision(false); //Set collision to false at the start
	attack1->getColliderComponent()->setDimension(1.4f, 0.6f); //Set collider dimension
	//attack1->getColliderComponent()->setOffset(glm::vec3(0.85f, -1.0f, 0.0f)); //Set collider offset
	attack1->setDrawCollider(false);
	attack1->setShieldParent(this);
	chainAttackList.push_back(attack1);

	PlayerAttackCollider* attack2 = new PlayerAttackCollider(120, 30);
	attack2->setName("Attack2");
	attack2->setDraw(false);
	attack2->addColliderComponent();
	attack2->getColliderComponent()->setTrigger(true);
	attack2->getColliderComponent()->setEnableCollision(false); //Set collision to false at the start
	attack2->getColliderComponent()->setDimension(2.4f, 1.0f); //Set collider dimension
	//attack2->getColliderComponent()->setOffset(glm::vec3(1.55f, -1.0f, 0.0f)); //Set collider offset
	attack2->setDrawCollider(false);
	attack2->setShieldParent(this);
	chainAttackList.push_back(attack2);

	PlayerAttackCollider* attack3 = new PlayerAttackCollider(280, 0);
	attack3->initAnimation(0, 0);
	attack3->getAnimationComponent()->addState("explosion", 0, 10);
	attack3->getAnimationComponent()->setLoop(false);
	attack3->setName("SmallUlt");
	attack3->setDraw(false);
	attack3->getTransform().setScale(glm::vec3(5.0f, 5.0f, 5.0f));
	attack3->addColliderComponent();
	attack3->getColliderComponent()->setTrigger(true);
	attack3->getColliderComponent()->setEnableCollision(false); //Set collision to false at the start
	attack3->getColliderComponent()->setDimension(1.0f, 1.0f); //Set collider dimension
	//attack2->getColliderComponent()->setOffset(glm::vec3(1.55f, -1.0f, 0.0f)); //Set collider offset
	attack3->setDrawCollider(false);
	attack3->setShieldParent(this);
	chainAttackList.push_back(attack3);

	PlayerAttackCollider* attack4 = new PlayerAttackCollider(1400, 0);
	attack4->initAnimation(0, 0);
	attack4->getAnimationComponent()->addState("explosion", 0, 12);
	attack4->getAnimationComponent()->setLoop(false);
	attack4->setName("BigUlt");
	attack4->setDraw(false);
	attack4->getTransform().setScale(glm::vec3(7.5f, 7.5f, 7.5f));
	attack4->addColliderComponent();
	attack4->getColliderComponent()->setTrigger(true);
	attack4->getColliderComponent()->setEnableCollision(false); //Set collision to false at the start
	attack4->getColliderComponent()->setDimension(1.0f, 1.0f); //Set collider dimension
	//attack2->getColliderComponent()->setOffset(glm::vec3(1.55f, -1.0f, 0.0f)); //Set collider offset
	attack4->setDrawCollider(false);
	attack4->setShieldParent(this);
	chainAttackList.push_back(attack4);
}

Shield::~Shield() {
	/*for (auto obj : chainAttackList) {
		delete obj;
	}*/
	chainAttackList.clear();
}

void Shield::update(float dt, Player* playerObject) {
	list<DrawableObject*>::iterator itr = chainAttackList.begin();
	glm::vec3 playerPos = playerObject->getTransform().getPosition();

	for (auto obj : chainAttackList) {

		if (!canDrawCollider) {
			obj->setCanDrawColliderNew(false);
		}
		else {
			obj->setCanDrawColliderNew(true);
		}

		PlayerAttackCollider* col = dynamic_cast<PlayerAttackCollider*>(obj);

		if (!col) {
			return;
		}

		if (col->getCanDraw()) {
			if (!col->getAnimationComponent()->getAnimationCompleted()) {
				return;
			}
		}

		if (obj->getName() == "Attack1") {
			obj->getTransform().setPosition(playerPos + attack1Offset);
			flipOffset(obj, playerObject);
		}
		else if (obj->getName() == "Attack2") {
			obj->getTransform().setPosition(playerPos + attack2Offset);
			flipOffset(obj, playerObject);
		}
		else if (obj->getName() == "SmallUlt") {
			obj->getTransform().setPosition(playerPos + smallUltOffset);
			flipOffset(obj, playerObject);
		}
		else if (obj->getName() == "BigUlt") {
			obj->getTransform().setPosition(playerPos + bigUltOffset);
			flipOffset(obj, playerObject);
		}
	}
}

void Shield::flipOffset(DrawableObject* obj, Player* playerObject) {
	if (!playerObject) return;
	if (playerObject->getFacingRight()) return;

	glm::vec3 newPos = playerObject->getTransform().getPosition();

	if (obj->getName() == "Attack1") {
		newPos.x = newPos.x - attack1Offset.x;
		newPos.y = newPos.y + attack1Offset.y;
		obj->getTransform().setPosition(newPos);
	}
	else if (obj->getName() == "Attack2") {
		newPos.x = newPos.x - attack2Offset.x;
		newPos.y = newPos.y + attack2Offset.y;
		obj->getTransform().setPosition(newPos);
	}
	else if (obj->getName() == "SmallUlt") {
		newPos.x = newPos.x - smallUltOffset.x;
		newPos.y = newPos.y + smallUltOffset.y;
		obj->getTransform().setPosition(newPos);
	}
	else if (obj->getName() == "BigUlt") {
		newPos.x = newPos.x - bigUltOffset.x;
		newPos.y = newPos.y + bigUltOffset.y;
		obj->getTransform().setPosition(newPos);
	}
}

void Shield::chainAttack() { //Unused
	list<DrawableObject*>::iterator itr = chainAttackList.begin();

	switch (currentChainAttack) {
	case 0: // Start of the chain attack
		//Change player animation
		//Enable first chainAttackList object hitbox
		if (itr != chainAttackList.end() && *itr != nullptr) {
			DrawableObject* attack = *itr;
			attack->setDrawCollider(true);
			inChainAttack = true;
		}
	}
}

list<DrawableObject*> Shield::getChainAttackList() const {
	return chainAttackList;
}

void Shield::setCurrentChainAttack(int i) {
	currentChainAttack = i;
}

int Shield::getCurrentChainAttack() const {
	return currentChainAttack;
}

void Shield::setInChainAttack(bool s) {
	inChainAttack = s;
}

bool Shield::getInChainAttack() const {
	return inChainAttack;
}

void Shield::setInputBuffer(bool s) {
	inputBuffer = s;
}

bool Shield::getInputBuffer() const {
	return inputBuffer;
}

DrawableObject* Shield::getChainAttackObject(int index) {
	if (index < 0 || index >= chainAttackList.size()) {
		return nullptr;
	}

	auto it = chainAttackList.begin();
	std::advance(it, index);
	return *it;
}

void Shield::setIsHolding(bool s) {
	isHolding = s;
}

bool Shield::getIsHolding() const {
	return isHolding;
}

void Shield::setIsBlocking(bool s) {
	isBlocking = s;
}

bool Shield::getIsBlocking() const {
	return isBlocking;
}

void Shield::setIsPerfect(bool s) {
	isPerfect = s;
}

bool Shield::getIsPerfect() const {
	return isPerfect;
}

bool* Shield::getCanDrawColliderAddress() {
	return &canDrawCollider;
}

void Shield::setSmallUltReady(bool v) {
	smallUltReady = v;
}

bool Shield::getSmallUltReady() const {
	return smallUltReady;
}

void Shield::setBigUltReady(bool v) {
	bigUltReady = v;
}

bool Shield::getBigUltReady() const {
	return bigUltReady;
}