#pragma once
#include "TexturedObject.h"

class EnemyAttackCollider;

class Enemy : public TexturedObject {
	float damage;

	float attackTimer = 0.75f;
	float attackTimeElapsed = 0.0f;

	EnemyAttackCollider* attackCollider;

public:
	Enemy();
	Enemy(float damage_);
	void selfUpdate(float dt);
	DrawableObject* getEnemyAttackCollider();
};