#pragma once
#include "BossStateM.h"
#include "Ziz.h"
#include "Level.h"
#include "Player.h"
#include "EnemyAttackCollider.h"

class Ziz;

class ZizGroundSlamState : public BossStateM {
	private:
		static ZizGroundSlamState* instance;

		bool hasFlew;
		bool isAtMaxAlt;
		bool hasSlammed;
		bool isSlamming;
		bool tooClose;
		bool wayTooClose;
		int faceDirection; //-1 for facing left, 1 for facing right


		Ziz* ziz;
		Player* player;
		EnemyAttackCollider* attackCollider;
		glm::vec3 targetPos;
		glm::vec3 endPos;
		glm::vec3 startPos;
		glm::vec3 newPos;

		float inAirTimer;
		float slamTimer;
		const float slamDuration = 0.08f * 3;
		float t;
		float endPosOffset;

		float recoveryTimer;

	public:
		
		
		static ZizGroundSlamState* getInstance();

		void enter(Boss* boss) override;

		void update(Boss* boss, float dt) override;

		void exit(Boss* boss) override;

};

