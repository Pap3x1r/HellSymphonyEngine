#include "Enemy.h"
#include "EnemyAttackCollider.h"

Enemy::Enemy(float damage_) {
	damage = damage_;
	glm::vec3 currentPos = getTransform().getPosition();
	getTransform().setPosition(currentPos.x + 2.0f, currentPos.y - 1.6f);
	setDraw(false);
	//Collider
	addColliderComponent();
	getColliderComponent()->setTrigger(true);
	getColliderComponent()->setDimension(1.0f, 1.5f);
	getColliderComponent()->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	setDrawCollider(true);
	//Physics

	//Attack collider
	attackCollider = new EnemyAttackCollider(5);
	attackCollider->setDraw(false);
	attackCollider->setDrawCollider(false);
	attackCollider->addColliderComponent();
	attackCollider->getColliderComponent()->setEnableCollision(false);
	attackCollider->getColliderComponent()->setTrigger(true);
	attackCollider->getColliderComponent()->setDimension(1.0f, 1.0f);
	attackCollider->getColliderComponent()->setOffset(glm::vec3(-1.1f, 0.0f, 0.0f));
}

void Enemy::selfUpdate(float dt) {
	attackTimeElapsed += dt;

	if (attackTimeElapsed >= attackTimer) {
		attackTimeElapsed = 0.0f;

		if (attackCollider->getColliderComponent()->isEnable()) {
			attackCollider->getColliderComponent()->setEnableCollision(false);
			attackCollider->setDrawCollider(false);
		} else {
			attackCollider->getColliderComponent()->setEnableCollision(true);
			attackCollider->setDrawCollider(true);
		}
	}
}

DrawableObject* Enemy::getEnemyAttackCollider() {
	return attackCollider;
}