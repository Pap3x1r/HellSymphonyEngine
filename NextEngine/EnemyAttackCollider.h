#pragma once
#include "TexturedObject.h"
#include "Player.h"
#include "Enemy.h"

class EnemyAttackCollider : public TexturedObject {
	float damage;
	bool hasHit = false;
	bool playerInside = false;
public:
	EnemyAttackCollider(float damage_);

	void onCollisionEnter(Collider* collider) override;
	void onCollisionStay(Collider* collider) override;
	void onCollisionExit(Collider* collider) override;
	void onTriggerEnter(Collider* collider) override;
	void onTriggerStay(Collider* collider) override;
	void onTriggerExit(Collider* collider) override;
	void resetHit();
	void setPlayerInside(bool inside);
	bool getPlayerInside() const;
};