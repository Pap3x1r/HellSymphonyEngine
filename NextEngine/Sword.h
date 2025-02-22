#pragma once
#include <list>
#include "Player.h"
#include "PlayerAttackCollider.h"

using namespace std;

class Sword {

	int currentChainAttack = 0;
	int maxChainAttack = 5;

	float attackTimeElapsed = 0.0f; // Do not change
	float attackTimeWindow = 0.5f; //

	bool inChainAttack = false;
	bool inputBuffer = false;

	glm::vec3 attack1Offset = { 0.85f, -1.0f, 0.0f };
	glm::vec3 attack2Offset = { 1.55f, -1.0f, 0.0f };
	glm::vec3 attack3Offset = { 2.05f, -1.0f, 0.0f };
	glm::vec3 heavyAttackOffset = { 2.05f, -1.0f, 0.0f };

	//Light attack (left click)
	list<DrawableObject*> chainAttackList;

public:

	Sword() {
		PlayerAttackCollider* attack1 = new PlayerAttackCollider(10, 100);
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

		PlayerAttackCollider* attack3 = new PlayerAttackCollider(30, 100);
		attack3->setName("Attack3");
		attack3->setDraw(false);
		attack3->addColliderComponent();
		attack3->getColliderComponent()->setTrigger(true);
		attack3->getColliderComponent()->setEnableCollision(false); //Set collision to false at the start
		attack3->getColliderComponent()->setDimension(4.0f, 2.0f); //Set collider dimension
		//attack3->getColliderComponent()->setOffset(glm::vec3(2.05f, -1.0f, 0.0f)); //Set collider offset
		attack3->setDrawCollider(false);
		chainAttackList.push_back(attack3);

		PlayerAttackCollider* heavyAttack = new PlayerAttackCollider(50, 100);
		heavyAttack->setName("heavyAttack");
		heavyAttack->setDraw(false);
		heavyAttack->addColliderComponent();
		heavyAttack->getColliderComponent()->setTrigger(true);
		heavyAttack->getColliderComponent()->setEnableCollision(false); //Set collision to false at the start
		heavyAttack->getColliderComponent()->setDimension(4.0f, 3.0f); //Set collider dimension
		//heavyAttack->getColliderComponent()->setOffset(glm::vec3(2.05f, -1.0f, 0.0f)); //Set collider offset
		heavyAttack->setDrawCollider(false);
		chainAttackList.push_back(heavyAttack);
	}

	~Sword() {
		for (auto obj : chainAttackList) {
			delete obj;
		}
	}

	void update(float dt, Player* playerObject) {
		list<DrawableObject*>::iterator itr = chainAttackList.begin();
		glm::vec3 playerPos = playerObject->getTransform().getPosition();

		for (auto obj : chainAttackList) {
			//obj->getTransform().setPosition(glm::vec3(playerPos.x + 0.85f, playerPos.y - 1.0f, playerPos.z));
			obj->getTransform().setPosition(playerPos);
			flipOffset(obj, playerObject);
		}
	}

	void flipOffset(DrawableObject* object, Player* playerObject) {
		if (!playerObject) return;


		//glm::vec3 newOffset = object->getColliderComponent()->getOffset();
		//newOffset.x = playerObject->getFacingRight() ? glm::abs(newOffset.x) : -glm::abs(newOffset.x);
		//object->getColliderComponent()->setOffset(newOffset);
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
};