#include "EnemyAttackCollider.h"
#include "Shield.h"

EnemyAttackCollider::EnemyAttackCollider() {
	damage = 0.0f;
	setName("EnemyAttackCollider");
}

EnemyAttackCollider::EnemyAttackCollider(float damage_) {
	damage = damage_;
	setName("EnemyAttackCollider");
}

void EnemyAttackCollider::onCollisionEnter(Collider* collider) {
	DrawableObject* obj = collider->getObject();
	Player* player = dynamic_cast<Player*>(obj);

	if (player) {
		//cout << "Enemy Hit Player for " << damage << " damage." << endl;
		//cout << "onCollisionEnter fired" << endl;
	}
}

void EnemyAttackCollider::onCollisionStay(Collider* collider) {
	DrawableObject* obj = collider->getObject();
	Player* player = dynamic_cast<Player*>(obj);

	if (player) {
		//playerInside = true;
		if (!hasHit) {

			if (player->getShield()->getIsBlocking()) { // is blocking
				if (player->getShield()->getIsPerfect()) { //is perfectly timed
					cout << "Player perfect blocked" << endl;
					player->increaseUltimateGauge(100.0f); //instant fill
					hasHit = true;
				}
				else { //if blocking but not perfectly
					cout << "Enemy Hit Player for " << damage/2 << " damage and " << damage/2 << "withered damage." << endl;
					player->getHealth()->takeDamage(damage, 30);
					player->increaseUltimateGauge(damage / 2); // increase by withered damage.
					hasHit = true;
				}
			}
			else { //is not blocking
				cout << "Enemy Hit Player for " << damage << " damage." << endl;
				player->getHealth()->takeDamage(damage);
				hasHit = true;
			}
		}

	}
}

void EnemyAttackCollider::onCollisionExit(Collider* collider) {
	DrawableObject* obj = collider->getObject();
}

void EnemyAttackCollider::onTriggerEnter(Collider* collider) {
	DrawableObject* obj = collider->getObject();
	Player* player = dynamic_cast<Player*>(obj);

	if (player) {
		cout << "onTriggerEnter fired" << endl;
	}
}

void EnemyAttackCollider::onTriggerStay(Collider* collider) {
	DrawableObject* obj = collider->getObject();

	Player* player = dynamic_cast<Player*>(obj);

	/*if (player) {
		playerInside = true;
		if (!hasHit) {
			cout << "hit player" << endl;
			hasHit = true;
		}
		
	}*/
}

void EnemyAttackCollider::onTriggerExit(Collider* collider) {
	DrawableObject* obj = collider->getObject();
	Player* player = dynamic_cast<Player*>(obj);
	/*if (player) {
		playerInside = false;
		cout << "player is out" << endl;

	}*/
}

void EnemyAttackCollider::resetHit() {
	hasHit = false;
}

void EnemyAttackCollider::setPlayerInside(bool inside) {
	playerInside = inside;
}

bool EnemyAttackCollider::getPlayerInside() const {
	return playerInside;
}