#include "PlayerAttackCollider.h"

void PlayerAttackCollider::onCollisionEnter(Collider* collider) {
	DrawableObject* obj = collider->getObject();
	Player* player = dynamic_cast<Player*>(obj);

	if (player) {
		//cout << "hit player" << endl;
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
}

void PlayerAttackCollider::onTriggerStay(Collider* collider) {
	DrawableObject* obj = collider->getObject();
	Enemy* enemy = dynamic_cast<Enemy*>(obj);

	if (enemy) {
		cout << "hit enemy" << endl;
	}
}

void PlayerAttackCollider::onTriggerExit(Collider* collider) {
	DrawableObject* obj = collider->getObject();
}