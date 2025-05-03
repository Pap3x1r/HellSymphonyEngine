#pragma once
#include "TexturedObject.h"
#include "Player.h"
#include "Enemy.h"

class EnemyAttackCollider : public TexturedObject {
	float damage;
	float knockbackForce = 0.0f;
	float knockbackTimer = 0.0f;
	bool hasHit = false;
	bool playerInside = false;
	bool willKnockBack = false;
public:
	EnemyAttackCollider();
	EnemyAttackCollider(float damage_);
	EnemyAttackCollider(float damage_, float force, float duration);

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