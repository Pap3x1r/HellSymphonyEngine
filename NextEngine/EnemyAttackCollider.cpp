#include "EnemyAttackCollider.h"

EnemyAttackCollider::EnemyAttackCollider(float damage_) {
	damage = damage_;
}

void EnemyAttackCollider::onCollisionEnter(Collider* collider) {
	DrawableObject* obj = collider->getObject();
	Player* player = dynamic_cast<Player*>(obj);

	if (player) {
		cout << "Enemy Hit Player for " << damage << " damage." << endl;
	}
}

void EnemyAttackCollider::onCollisionStay(Collider* collider) {
	DrawableObject* obj = collider->getObject();
	Player* player = dynamic_cast<Player*>(obj);

	/*if (player) {
		cout << "hit player" << endl;
	}*/
}

void EnemyAttackCollider::onCollisionExit(Collider* collider) {
	DrawableObject* obj = collider->getObject();
}

void EnemyAttackCollider::onTriggerEnter(Collider* collider) {
	DrawableObject* obj = collider->getObject();

	Player* player = dynamic_cast<Player*>(obj);

	if (player) {
		cout << "hit player" << endl;
	}
}

void EnemyAttackCollider::onTriggerStay(Collider* collider) {
	DrawableObject* obj = collider->getObject();
}

void EnemyAttackCollider::onTriggerExit(Collider* collider) {
	DrawableObject* obj = collider->getObject();
}