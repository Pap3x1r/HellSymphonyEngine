#pragma once
#include "DrawableObject.h"
#include "Boss.h"
#include "Player.h"
#include "Ziz.h"
#include "EnemyAttackCollider.h"
#include <random>

class Impale : public TexturedObject {
private:
	bool hasStruck;
	bool deletedAtk;

	float timer;
	float attackTimer;
	float hitboxTimer;
	float attackDurationTimer;
	EnemyAttackCollider* attackCollider;
	Ziz* ziz;


public:

	Impale();
	Impale(Ziz* boss);
	void update(float dt);

};