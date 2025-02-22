#pragma once
#include "TexturedObject.h"
#include "Player.h"
#include "Enemy.h"

class PlayerAttackCollider : public TexturedObject {
	float damage;
	bool hasHit = false;
	float ultGainPercentage;
	Player* player;
public:
	PlayerAttackCollider();
	PlayerAttackCollider(float damage_);
	PlayerAttackCollider(float damage_, float ultPercentage_);
	void onCollisionEnter(Collider* collider) override;
	void onCollisionStay(Collider* collider) override;
	void onCollisionExit(Collider* collider) override;
	void onTriggerEnter(Collider* collider) override;
	void onTriggerStay(Collider* collider) override;
	void onTriggerExit(Collider* collider) override;
	void resetHit();
	void setPlayer(Player* p);
};
