#pragma once
#include <list>
#include "Player.h"
#include "PlayerAttackCollider.h"

using namespace std;

class Shield {

	int currentChainAttack = 0;

	bool isHolding = false; //True at the start, false at the end of shield animation
	bool isBlocking = false; //Only true when shield is fully up
	bool isPerfect = false; //Only true when shield is fully up and the time window is perfect

	float attackTimeElapsed = 0.0f; // Do not change
	float attackTimeWindow = 0.5f; //

	bool inChainAttack = false;
	bool inputBuffer = false;

	glm::vec3 attack1Offset = { 0.85f, -1.0f, 0.0f };
	glm::vec3 attack2Offset = { 1.55f, -1.0f, 0.0f };
	glm::vec3 smallUltOffset = { 0.0f, -1.0f, 0.0f };
	glm::vec3 bigUltOffset = { 0.0f, -1.0f, 0.0f };

	//Light attack (left click)
	list<DrawableObject*> chainAttackList;

public:

	Shield() {
		PlayerAttackCollider* attack1 = new PlayerAttackCollider(10, 100); //Change damage and ult gain percentage here
		attack1->setName("Attack1");
		attack1->setDraw(false);
		attack1->addColliderComponent();
		attack1->getColliderComponent()->setTrigger(true);
		attack1->getColliderComponent()->setEnableCollision(false); //Set collision to false at the start
		attack1->getColliderComponent()->setDimension(1.4f, 0.6f); //Set collider dimension
		//attack1->getColliderComponent()->setOffset(glm::vec3(0.85f, -1.0f, 0.0f)); //Set collider offset
		attack1->setDrawCollider(false);
		chainAttackList.push_back(attack1);

		PlayerAttackCollider* attack2 = new PlayerAttackCollider(20, 100);
		attack2->setName("Attack2");
		attack2->setDraw(false);
		attack2->addColliderComponent();
		attack2->getColliderComponent()->setTrigger(true);
		attack2->getColliderComponent()->setEnableCollision(false); //Set collision to false at the start
		attack2->getColliderComponent()->setDimension(2.4f, 1.0f); //Set collider dimension
		//attack2->getColliderComponent()->setOffset(glm::vec3(1.55f, -1.0f, 0.0f)); //Set collider offset
		attack2->setDrawCollider(false);
		chainAttackList.push_back(attack2);

		PlayerAttackCollider* attack3 = new PlayerAttackCollider(100, 0);
		attack3->setName("SmallUlt");
		attack3->setDraw(false);
		attack3->addColliderComponent();
		attack3->getColliderComponent()->setTrigger(true);
		attack3->getColliderComponent()->setEnableCollision(false); //Set collision to false at the start
		attack3->getColliderComponent()->setDimension(3.0f, 3.0f); //Set collider dimension
		//attack2->getColliderComponent()->setOffset(glm::vec3(1.55f, -1.0f, 0.0f)); //Set collider offset
		attack3->setDrawCollider(false);
		chainAttackList.push_back(attack3);

		PlayerAttackCollider* attack4 = new PlayerAttackCollider(200, 0);
		attack4->setName("BigUlt");
		attack4->setDraw(false);
		attack4->addColliderComponent();
		attack4->getColliderComponent()->setTrigger(true);
		attack4->getColliderComponent()->setEnableCollision(false); //Set collision to false at the start
		attack4->getColliderComponent()->setDimension(3.0f, 3.0f); //Set collider dimension
		//attack2->getColliderComponent()->setOffset(glm::vec3(1.55f, -1.0f, 0.0f)); //Set collider offset
		attack4->setDrawCollider(false);
		chainAttackList.push_back(attack4);
	}

	~Shield() {
		for (auto obj : chainAttackList) {
			delete obj;
		}
	}

	void update(float dt, Player* playerObject) {
		list<DrawableObject*>::iterator itr = chainAttackList.begin();
		glm::vec3 playerPos = playerObject->getTransform().getPosition();

		for (auto obj : chainAttackList) {
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

	void flipOffset(DrawableObject* obj, Player* playerObject) {
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

	void chainAttack() { //Unused
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

	list<DrawableObject*> getChainAttackList() const {
		return chainAttackList;
	}

	void setCurrentChainAttack(int i) {
		currentChainAttack = i;
	}

	int getCurrentChainAttack() const {
		return currentChainAttack;
	}

	void setInChainAttack(bool s) {
		inChainAttack = s;
	}

	bool getInChainAttack() const {
		return inChainAttack;
	}

	void setInputBuffer(bool s) {
		inputBuffer = s;
	}

	bool getInputBuffer() const {
		return inputBuffer;
	}

	DrawableObject* getChainAttackObject(int index) {
		if (index < 0 || index >= chainAttackList.size()) {
			return nullptr;
		}

		auto it = chainAttackList.begin();
		std::advance(it, index);
		return *it;
	}

	void setIsHolding(bool s) {
		isHolding = s;
	}

	bool getIsHolding() const {
		return isHolding;
	}

	void setIsBlocking(bool s) {
		isBlocking = s;
	}

	bool getIsBlocking() const {
		return isBlocking;
	}

	void setIsPerfect(bool s) {
		isPerfect = s;
	}

	bool getIsPerfect() const {
		return isPerfect;
	}
};