#pragma once
#include "DrawableObject.h"
#include "Boss.h"
#include "Player.h"
#include "Ziz.h"
#include "EnemyAttackCollider.h"
#include <random>
#include <chrono>

class Lightning : public TexturedObject {
private:
	bool hasStruck;
	bool deletedAtk;

	float timer;
	float attackTimer;
	float attackDurationTimer;
	EnemyAttackCollider* attackCollider;
	Ziz* ziz;
	std::mt19937 gen;
	std::uniform_real_distribution<> randomX;

public:

	Lightning();
	Lightning(Ziz* boss);
	void update(float dt);

};