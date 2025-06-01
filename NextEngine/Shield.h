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

	bool canDrawCollider = false;

	bool smallUltReady = true;
	bool bigUltReady = true;

public:

	Shield();

	~Shield();

	void update(float dt, Player* playerObject);

	void flipOffset(DrawableObject* obj, Player* playerObject);

	void chainAttack();

	list<DrawableObject*> getChainAttackList() const;

	void setCurrentChainAttack(int i);

	int getCurrentChainAttack() const;

	void setInChainAttack(bool s);

	bool getInChainAttack() const;

	void setInputBuffer(bool s);

	bool getInputBuffer() const;

	DrawableObject* getChainAttackObject(int index);

	void setIsHolding(bool s);
	bool getIsHolding() const;

	void setIsBlocking(bool s);
	bool getIsBlocking() const;

	void setIsPerfect(bool s);
	bool getIsPerfect() const;

	bool* getCanDrawColliderAddress();

	void setSmallUltReady(bool v);
	bool getSmallUltReady() const;

	void setBigUltReady(bool v);
	bool getBigUltReady() const;
};