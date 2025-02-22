#include "PlayerAttackCollider.h"

PlayerAttackCollider::PlayerAttackCollider() {
	damage = 0;
}

PlayerAttackCollider::PlayerAttackCollider(float damage_) {
	damage = damage_;
}

void PlayerAttackCollider::onCollisionEnter(Collider* collider) {
	DrawableObject* obj = collider->getObject();
	Enemy* enemy = dynamic_cast<Enemy*>(obj);

	if (enemy) {
		cout << "hit enemy" << endl;
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

	if (enemy) {
		//playerInside = true;
		if (!hasHit) {
			cout << "Player Hit Enemy for " << damage << " damage." << endl;
			hasHit = true;
		}

	}
}

void PlayerAttackCollider::onTriggerExit(Collider* collider) {
	DrawableObject* obj = collider->getObject();
}

void PlayerAttackCollider::resetHit() {
	hasHit = false;
}