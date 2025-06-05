#pragma once
#include "Arrow.h"
#include "BowUltimateCollider.h"

class Player;

class Bow {
	float rapidShotTimer = 0.15f;
	float rapidShotTimeElapsed = rapidShotTimer;
	bool rapidShotReady = false;

	float currentRapidOverheat = 0.0f;
	float maxRapidOverheat = 100.0f;
	float overheatPerArrow = 20.0f;
	float normalDecreaseRate = 25.0f;
	float overheatDecreaseRate = 22.5f;
	bool isOverheat = false;

	bool isShooting = false;

	bool rapidShotDebugMode = false;

	list<DrawableObject*> chainAttackList;

	bool smallUltReady = true;
	bool bigUltReady = true;

public:

	Bow();

	void update(float dt, Player* player);

	void setEnableDebug();

	void setIsShooting(bool value) {
		isShooting = value;
	}

	bool getIsShooting() const {
		return isShooting;
	}

	DrawableObject* arrowShot(float damage_, float ultPercentage_, Player* player, float speed);
	DrawableObject* arrowShot(float damage_, float ultPercentage_, Player* player, float speed, float overheat);

	bool getRapidShotReady() const;
	bool getIsOverheat() const;

	list<DrawableObject*> getChainAttackList() const {
		return chainAttackList;
	}

	DrawableObject* getChainAttackObject(int index) {
		if (index < 0 || index >= chainAttackList.size()) {
			return nullptr;
		}

		auto it = chainAttackList.begin();
		std::advance(it, index);
		return *it;
	}

	void setSmallUltReady(bool v);
	bool getSmallUltReady() const;

	void setBigUltReady(bool v);
	bool getBigUltReady() const;

	float getCurrentOverheat() {
		return currentRapidOverheat;
	}

	float getMaxOverheat() {
		return maxRapidOverheat;
	}
};
