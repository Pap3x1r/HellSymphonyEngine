#include "PlayerAttackCollider.h"
#include "Ziz.h"
#include "Lucifer.h"

PlayerAttackCollider::PlayerAttackCollider() {
	damage = 0;
	ultGainPercentage = 0;
	player = nullptr;
}

PlayerAttackCollider::PlayerAttackCollider(float damage_) {
	damage = damage_;
	ultGainPercentage = 0;
	player = nullptr;
}

PlayerAttackCollider::PlayerAttackCollider(float damage_, float ultPercentage_) {
	damage = damage_;
	ultGainPercentage = ultPercentage_;
	player = nullptr;
}

void PlayerAttackCollider::onCollisionEnter(Collider* collider) {
	DrawableObject* obj = collider->getObject();
	Enemy* enemy = dynamic_cast<Enemy*>(obj);

	if (enemy) {
		//cout << "hit enemy attack" << endl;
	}
}

void PlayerAttackCollider::onCollisionStay(Collider* collider) {
	DrawableObject* obj = collider->getObject();
	Player* player = dynamic_cast<Player*>(obj);

	if (player) {
		//cout << "hit player" << endl;
	}
}

void PlayerAttackCollider::onCollisionExit(Collider* collider) {
	DrawableObject* obj = collider->getObject();
}

void PlayerAttackCollider::onTriggerEnter(Collider* collider) {
	DrawableObject* obj = collider->getObject();
	Enemy* enemy = dynamic_cast<Enemy*>(obj);

	if (enemy) {
		//cout << "hit enemy" << endl;
	}
}

void PlayerAttackCollider::onTriggerStay(Collider* collider) {
	DrawableObject* obj = collider->getObject();
	Enemy* enemy = dynamic_cast<Enemy*>(obj);

	Ziz* ziz = Ziz::getInstance();
	Lucifer* lucifer = Lucifer::getInstance();


	if (enemy) {
		//playerInside = true;
		if (!hasHit) {
			cout << "Player Hit Enemy test for " << damage << " damage." << endl;
			if (player) {
				player->increaseUltimateGauge(ultGainPercentage);

				if (shieldParent) {
					player->getHealth()->healWither(damage / 25.0f);
				}
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

					if (shieldParent) {
						player->getHealth()->healWither(damage / 25.0f);
					}
					//cout << "Ult gauge increased by " << damage * ultGainPercentage / 100.0f << endl;
				}


				dummy->setHitEffectStrength(1.0f);

				hasHit = true;

				SoundManager::GetInstance()->PlaySFX("Misc-HitDummy");
			}
		}
	}
}

void PlayerAttackCollider::onTriggerExit(Collider* collider) {
	DrawableObject* obj = collider->getObject();
}

void PlayerAttackCollider::resetHit() {
	hasHit = false;
	//cout << "hasHit has been resetted" << endl;
}

void PlayerAttackCollider::setPlayer(Player* p) {
	player = p;
}

void PlayerAttackCollider::setShieldParent(Shield* s) {
	shieldParent = s;
}