#pragma once
#include "PlayerAttackCollider.h"
#include "Player.h"
#include "Enemy.h"
#include "Ziz.h"
#include "Lucifer.h"
#include "Bow.h"

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
	float hitCooldown = 0.083f * 3;

	glm::vec3 defaultPosition = { 0.0f,0.0f,0.0f };

public:
	BowUltimateCollider();
	BowUltimateCollider(float damage_);
	BowUltimateCollider(float damage_, float ultPercentage_);
	BowUltimateCollider(float damage_, float ultPercentage_, float xOffset_);

	void update(float dt);

	void onCollisionEnter(Collider* collider) override;
	void onCollisionStay(Collider* collider) override;
	void onCollisionExit(Collider* collider) override;
	void onTriggerEnter(Collider* collider) override;
	void onTriggerStay(Collider* collider) override;
	void onTriggerExit(Collider* collider) override;

	float getXOffset() const;

	void resetHit();

	void setPlayer(Player* p);

	void setEnable(bool value);

	void setTimeLimit(float value);

	void setHitCooldown(float value);
};
