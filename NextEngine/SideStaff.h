#pragma once
#include "DrawableObject.h"
#include "Lucifer.h"
#include "EnemyAttackCollider.h"
#include <iostream>

class SideStaff : public TexturedObject {
private:

	Lucifer* lucifer;

	float timer;
	bool spawnedLaser;
	float spawnLaser;

	EnemyAttackCollider* atk;

public:

	SideStaff();

	void update(float dt);
};