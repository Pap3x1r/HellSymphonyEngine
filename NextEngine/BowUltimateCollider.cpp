#include "BowUltimateCollider.h"

BowUltimateCollider::BowUltimateCollider() {
	damage = 0;
	ultGainPercentage = 0;
}

BowUltimateCollider::BowUltimateCollider(float damage_) {
	damage = damage_;
	ultGainPercentage = 0;
}

BowUltimateCollider::BowUltimateCollider(float damage_, float ultPercentage_) {
	damage = damage_;
	ultGainPercentage = ultPercentage_;
}

BowUltimateCollider::BowUltimateCollider(float damage_, float ultPercentage_, float xOffset_) {
	damage = damage_;
	ultGainPercentage = ultPercentage_;
	xOffset = xOffset_;
}

void BowUltimateCollider::update(float dt) {
	if (isEnable) {
		timeElapsed += dt;
		timeEnabled += dt;

		//cout << "timeElapsed " << timeElapsed << " timeEnabled: " << timeEnabled << endl;

		if (timeElapsed >= hitCooldown) {
			resetHit();
		}

		if (timeEnabled >= timeLimit) {
			isEnable = false;
			timeElapsed = 0.0f;
			timeEnabled = 0.0f;
			setDrawCollider(false);
			setDraw(false);
			getColliderComponent()->setEnableCollision(false);
			if (player->getBow()->getChainAttackObject(0) == this) {
				player->getBow()->setSmallUltReady(true);
			}
			else {
				player->getBow()->setBigUltReady(true);
			}
		}
	}
}

void BowUltimateCollider::onCollisionEnter(Collider* collider) {

}

void BowUltimateCollider::onCollisionStay(Collider* collider) {

}

void BowUltimateCollider::onCollisionExit(Collider* collider) {

}
void BowUltimateCollider::onTriggerEnter(Collider* collider) {

}

void BowUltimateCollider::onTriggerStay(Collider* collider) {
	DrawableObject* obj = collider->getObject();

	Enemy* enemy = dynamic_cast<Enemy*>(obj);
	Ziz* ziz = Ziz::getInstance();
	Lucifer* lucifer = Lucifer::getInstance();

	if (enemy) {
		//playerInside = true;
		if (!hasHit) {
			//cout << "Player Hit Enemy for " << damage << " damage." << endl;
			if (player) {
				player->increaseUltimateGauge(damage * ultGainPercentage / 100.0f);
				//cout << "Ult gauge increased by " << damage * ultGainPercentage / 100.0f << endl;
			}

			if (GameEngine::getInstance()->getStateController()->gameStateCurr == GameState::GS_ZIZ) {
				if (ziz) {
					if (ziz->getIsInvincible() == false) {
						ziz->getHealth()->takeDamage(damage);
						ziz->setHitEffectStrength(1.0f);
						SoundManager::GetInstance()->PlaySFX("Misc-HitEnemy");
					}
				}
			}

			if (GameEngine::getInstance()->getStateController()->gameStateCurr == GameState::GS_LUCIFER) {
				if (lucifer) {
					if (lucifer->getIsInvincible() == false) {
						lucifer->startShake(0.1f, 0.002f);
						lucifer->getHealth()->takeDamage(damage);
						lucifer->setHitEffectStrength(1.0f);
						SoundManager::GetInstance()->PlaySFX("Misc-HitEnemy");
					}
				}
			}
			hasHit = true;
		}

	}

	InteractableObject* dummy = dynamic_cast<InteractableObject*>(obj);
	if (dummy) {
		if (dummy->getCanHit()) {
			if (!hasHit) {
				if (player) {
					player->increaseUltimateGauge(ultGainPercentage);
					//cout << "Ult gauge increased by " << damage * ultGainPercentage / 100.0f << endl;
				}


				dummy->setHitEffectStrength(1.0f);
				SoundManager::GetInstance()->PlaySFX("Misc-HitDummy");

				hasHit = true;
			}
		}
	}
}

void BowUltimateCollider::onTriggerExit(Collider* collider)  {

}

float BowUltimateCollider::getXOffset() const {
	return xOffset;
}

void BowUltimateCollider::resetHit() {
	hasHit = false;
	timeElapsed -= hitCooldown;
}

void BowUltimateCollider::setPlayer(Player* p) {
	player = p;
}

void BowUltimateCollider::setEnable(bool value) {
	isEnable = value;
}

void BowUltimateCollider::setTimeLimit(float value) {
	timeLimit = value;
}

void BowUltimateCollider::setHitCooldown(float value) {
	hitCooldown = value;
}