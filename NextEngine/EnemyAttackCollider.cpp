#include "EnemyAttackCollider.h"
#include "Shield.h"
#include "Ziz.h"

EnemyAttackCollider::EnemyAttackCollider() {
	setTag(Tag::EnemyAttack);
	damage = 0.0f;
	setName("EnemyAttackCollider");
}

EnemyAttackCollider::EnemyAttackCollider(float damage_) {
	setTag(Tag::EnemyAttack);
	damage = damage_;
	setName("EnemyAttackCollider");
}

EnemyAttackCollider::EnemyAttackCollider(float damage_, float force, float duration) {
	setTag(Tag::EnemyAttack);
	damage = damage_;
	setName("EnemyAttackCollider");
	willKnockBack = true;
	knockbackForce = force;
	knockbackTimer = duration;
	cout << "This attack will knockback" << endl;
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
	Ziz* ziz = Ziz::getInstance();

	if (player) {
		//playerInside = true;

		if (player->getInvincible() || player->getIsDashing()) {
			return;
		}

		if (!hasHit) {

			if (player->getShield()->getIsBlocking()) { // is blocking
				if (player->getShield()->getIsPerfect()) { //is perfectly timed
					cout << "Player perfect blocked" << endl;
					player->increaseUltimateGauge(100.0f); //instant fill
					hasHit = true;
					player->setNewColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
					player->setHitEffectStrength(1.0f);
					SoundManager::GetInstance()->PlaySFX("Dante-Shield_BlockPerfect");
				}
				else { //if blocking but not perfectly
					cout << "Enemy Hit Player for " << damage/2 << " damage and " << damage/2 << "withered damage." << endl;
					player->getHealth()->takeDamage(damage, 30);
					player->increaseUltimateGauge(damage / 2); // increase by withered damage.
					hasHit = true;
					player->setNewColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
					player->setHitEffectStrength(1.0f);
					SoundManager::GetInstance()->PlaySFX("Dante-Shield_Block");
				}
			}
			else { //is not blocking
				cout << "Enemy Hit Player for " << damage << " damage." << endl;
				player->getHealth()->takeDamage(damage);
				hasHit = true;
				player->startShake(0.1f, 0.0025f);
				player->setNewColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
				player->setHitEffectStrength(1.0f);
				if (willKnockBack == true) {
					if (player->getTransform().getPosition().x < ziz->getTransform().getPosition().x) { //player is left of ziz
						//cout << "knock left" << endl;
						player->stun(knockbackTimer);
						
						player->getPhysicsComponent()->addForce(glm::vec2(-knockbackForce, 0.25f));
						//player->getPhysicsComponent()->setVelocity(glm::vec2(player->getPhysicsComponent()->getVelocity().x, 0.0f)); //Set y velocity to 0 before jump to ensure player jump at the same height every time
						
						
						player->getStateMachine()->changeState(PlayerJumpUpState::getInstance(), player);
					}
					else {
						//cout << "knock right" << endl;
						player->stun(knockbackTimer);

						
						player->getPhysicsComponent()->addForce(glm::vec2(knockbackForce, 0.25));
						//player->getPhysicsComponent()->setVelocity(glm::vec2(player->getPhysicsComponent()->getVelocity().x, 0.0f)); //Set y velocity to 0 before jump to ensure player jump at the same height every time
						

						player->getStateMachine()->changeState(PlayerJumpUpState::getInstance(), player);
					}
				}
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