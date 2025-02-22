#pragma once
#include "TexturedObject.h"
#include "Player.h"
#include "Enemy.h"

class PlayerAttackCollider : public TexturedObject {
	float damage;
	bool hasHit = false;
public:
	PlayerAttackCollider();
	PlayerAttackCollider(float damage_);
	void onCollisionEnter(Collider* collider) override;
	void onCollisionStay(Collider* collider) override;
	void onCollisionExit(Collider* collider) override;
	void onTriggerEnter(Collider* collider) override;
	void onTriggerStay(Collider* collider) override;
	void onTriggerExit(Collider* collider) override;
	void resetHit();
};
