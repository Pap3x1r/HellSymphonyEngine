#pragma once
#include "BossStateM.h"
#include "Ziz.h"
#include "Level.h"
#include "EnemyAttackCollider.h"

class Ziz;

class ZizGroundSlamState : public BossStateM {
	private:
		static ZizGroundSlamState* instance;


		Ziz* ziz;
		EnemyAttackCollider* attackCollider;

	public:
		
		
		static ZizGroundSlamState* getInstance();

		void enter(Boss* boss) override;

		void update(Boss* boss, float dt) override;

		void exit(Boss* boss) override;

};

