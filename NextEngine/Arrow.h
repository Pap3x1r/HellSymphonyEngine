#pragma once
#include "PlayerAttackCollider.h"

class Arrow : public PlayerAttackCollider {
	float arrowSpeed;
	float damage;
	bool facingDirection;
	float timeToDestroy = 5.0f;
	float timeElapsed = 0.0f;

	bool readyToDestroy;
public:
	Arrow(float damage_, bool face, float speed);

	void selfUpdate(float dt);

	void onCollisionEnter(Collider* collider) override;
	void onCollisionStay(Collider* collider) override;
	void onCollisionExit(Collider* collider) override;
	void onTriggerEnter(Collider* collider) override;
	void onTriggerStay(Collider* collider) override;
	void onTriggerExit(Collider* collider) override;

	void setReadyToDestroy(bool value);

	bool getReadyToDestroy() const;
	bool getFacingDirection() const;
	float getArrowSpeed() const;

};