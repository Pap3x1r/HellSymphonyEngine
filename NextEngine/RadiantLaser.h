#pragma once
#include "DrawableObject.h"
#include "EnemyAttackCollider.h"
#include "Lucifer.h"
#include <iostream>

class RadiantLaser : public TexturedObject {
private:

	Lucifer* lucifer;

	float timer;
	bool spawnedAtk;
	float delay;

	EnemyAttackCollider* atkCollider1;
	EnemyAttackCollider* atkCollider2;
	EnemyAttackCollider* atkCollider3;
	EnemyAttackCollider* atkCollider4;
	EnemyAttackCollider* atkCollider5;

public:

	RadiantLaser();

	void update(float dt);
};