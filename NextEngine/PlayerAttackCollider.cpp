#include "PlayerAttackCollider.h"
#include "Ziz.h"

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
		cout << "hit enemy attack" << endl;
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
		cout << "hit enemy" << endl;
	}
}

void PlayerAttackCollider::onTriggerStay(Collider* collider) {
	DrawableObject* obj = collider->getObject();
	Enemy* enemy = dynamic_cast<Enemy*>(obj);

	DrawableObject* obj2 = collider->getObject();
	Ziz* ziz = dynamic_cast<Ziz*>(obj2);

	if (enemy) {
		//playerInside = true;
		if (!hasHit) {
			//cout << "Player Hit Enemy test for " << damage << " damage." << endl;
			if (player) {
				player->increaseUltimateGauge(damage * ultGainPercentage / 100.0f);
				//cout << "Ult gauge increased by " << damage * ultGainPercentage / 100.0f << endl;
			}

			if (ziz) {
				ziz->getHealth()->takeDamage(damage);
			}

			hasHit = true;
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