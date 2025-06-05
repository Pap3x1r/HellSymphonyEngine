#include "Arrow.h"
#include "Ziz.h"
#include "Lucifer.h"

Arrow::Arrow(float damage_, float ultPercentage_, bool face, float speed, Player* p) {
	arrowSpeed = speed;
	damage = damage_;
	facingDirection = face;
	readyToDestroy = false;
	player = p;
	ultGainPercentage = ultPercentage_;
}

void Arrow::selfUpdate(float dt) {
	timeElapsed += dt;

	if ((getTransform().getPosition().x > 8.0f) || (getTransform().getPosition().x < -8.0f)) {
		cout << "delete Arrow" << endl;
		DrawableObject::destroyObject(this);
	}

	/*if (!getMarkedForDelete()) {
		if (timeElapsed >= timeToDestroy) {
			DrawableObject::destroyObject(this);
		}
	}*/
}

void Arrow::onCollisionEnter(Collider* collider) {
	DrawableObject* obj = collider->getObject();
	

	Enemy* enemy = dynamic_cast<Enemy*>(obj);
	

	if (enemy) {
		cout << "Arrow hit ziz for " << damage << " damage." << endl;
		if (player) {
			
			player->increaseUltimateGauge(damage * ultGainPercentage / 100.0f);
			cout << "Ult gauge increased by " << damage * ultGainPercentage / 100.0f << endl;
		}
		
		

		//DrawableObject::destroyObject(this, objectsListRef);
		//setReadyToDestroy(true);
		DrawableObject::destroyObject(this);

		


	}
}

void Arrow::onCollisionStay(Collider* collider) {
	DrawableObject* obj = collider->getObject();
	Player* player = dynamic_cast<Player*>(obj);

	if (player) {
		//cout << "hit player" << endl;
	}
}

void Arrow::onCollisionExit(Collider* collider) {
	DrawableObject* obj = collider->getObject();
}

void Arrow::onTriggerEnter(Collider* collider) {
	DrawableObject* obj = collider->getObject();
	Enemy* enemy = dynamic_cast<Enemy*>(obj);

	Ziz* ziz = Ziz::getInstance();
	Lucifer* lucifer = Lucifer::getInstance();

	if (enemy) {
		//cout << "Arrow hit Enemy for " << damage << " damage." << endl;
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
		

		DrawableObject::destroyObject(this);
	}

	InteractableObject* dummy = dynamic_cast<InteractableObject*>(obj);
	if (dummy) {
		if (dummy->getCanHit()) {
			if (player) {
				player->increaseUltimateGauge(ultGainPercentage);
			}
			dummy->setHitEffectStrength(1.0f);
			DrawableObject::destroyObject(this);
			SoundManager::GetInstance()->PlaySFX("Misc-HitDummy");
		}
	}
}

void Arrow::onTriggerStay(Collider* collider) {
	DrawableObject* obj = collider->getObject();
	/*Enemy* enemy = dynamic_cast<Enemy*>(obj);

	if (enemy) {
		cout << "hit enemy" << endl;
		destroyObject(this, objectsListRef);
	}*/
}

void Arrow::onTriggerExit(Collider* collider) {
	DrawableObject* obj = collider->getObject();
}

void Arrow::setReadyToDestroy(bool value) {
	readyToDestroy = value;
}

bool Arrow::getReadyToDestroy() const {
	return readyToDestroy;
}

bool Arrow::getFacingDirection() const {
	return facingDirection;
}

float Arrow::getArrowSpeed() const {
	return arrowSpeed;
}