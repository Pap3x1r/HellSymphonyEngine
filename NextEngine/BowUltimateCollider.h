#pragma once
#include "PlayerAttackCollider.h"
#include "Player.h"
#include "Enemy.h"
#include "Ziz.h"

class BowUltimateCollider : public PlayerAttackCollider {
	float damage;
	float timeElapsed = 0.0f;
	bool hasHit = false;
	float ultGainPercentage;
	Player* player;

	float xOffset = 0.0f;

	bool isEnable = false;

	float timeEnabled = 0.0f;
	float timeLimit = 3.0f;

public:
	BowUltimateCollider() {
		damage = 0;
		ultGainPercentage = 0;
	}

	BowUltimateCollider(float damage_) {
		damage = damage_;
		ultGainPercentage = 0;
	}

	BowUltimateCollider(float damage_, float ultPercentage_) {
		damage = damage_;
		ultGainPercentage = ultPercentage_;
	}

	BowUltimateCollider(float damage_, float ultPercentage_, float xOffset_) {
		damage = damage_;
		ultGainPercentage = ultPercentage_;
		xOffset = xOffset_;
	}

	void update(float dt) {
		if (isEnable) {
			timeElapsed += dt;
			timeEnabled += dt;

			//cout << "timeElapsed " << timeElapsed << " timeEnabled: " << timeEnabled << endl;

			if (timeElapsed >= 1.0f) {
				resetHit();
			}

			if (timeEnabled >= timeLimit) {
				isEnable = false;
				timeEnabled = 0.0f;
				setDrawCollider(false);
				getColliderComponent()->setEnableCollision(false);
			}
		}
	}

	void onCollisionEnter(Collider* collider) override {

	}

	void onCollisionStay(Collider* collider) override {

	}

	void onCollisionExit(Collider* collider) override {

	}
	void onTriggerEnter(Collider* collider) override {

	}

	void onTriggerStay(Collider* collider) override {
		DrawableObject* obj = collider->getObject();
		DrawableObject* obj2 = collider->getObject();

		Enemy* enemy = dynamic_cast<Enemy*>(obj);
		Ziz* ziz = dynamic_cast<Ziz*>(obj2);

		if (enemy) {
			//playerInside = true;
			if (!hasHit) {
				//cout << "Player Hit Enemy for " << damage << " damage." << endl;
				if (player) {
					player->increaseUltimateGauge(damage * ultGainPercentage / 100.0f);
					//cout << "Ult gauge increased by " << damage * ultGainPercentage / 100.0f << endl;
				}

				if (ziz) {
					//cout << "ult hit ziz" << endl;
					ziz->getHealth()->takeDamage(damage);
					//cout << "ziz health from ult: " << ziz->getCurrentHealth() << endl;
				}

				hasHit = true;
			}

		}
	}

	void onTriggerExit(Collider* collider) override {

	}

	float getXOffset() const {
		return xOffset;
	}

	void resetHit() {
		hasHit = false;
		timeElapsed = 0.0f;
	}

	void setPlayer(Player* p) {
		player = p;
	}

	void setEnable(bool value) {
		isEnable = value;
	}
};
