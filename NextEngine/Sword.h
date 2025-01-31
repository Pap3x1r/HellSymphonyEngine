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

	//Light attack (left click)
	list<DrawableObject*> chainAttackList;

public:

	Sword() {
		PlayerAttackCollider* attack1 = new PlayerAttackCollider();
		attack1->setDraw(false);
		attack1->addColliderComponent();
		attack1->getColliderComponent()->setTrigger(true);
		attack1->getColliderComponent()->setEnableCollision(false); //Set collision to false at the start
		attack1->getColliderComponent()->setDimension(1.4f, 0.6f); //Set collider dimension
		attack1->getColliderComponent()->setOffset(glm::vec3(0.85f, -1.0f, 0.0f)); //Set collider offset
		attack1->setDrawCollider(false);
		chainAttackList.push_back(attack1);
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
		}
	}

	void chainAttack() {
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
};