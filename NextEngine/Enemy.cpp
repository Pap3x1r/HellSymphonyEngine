#include "Enemy.h"
#include "EnemyAttackCollider.h"

Enemy::Enemy() {
	cout << "Enemy Default Constructor" << endl;
	/*glm::vec3 currentPos = getTransform().getPosition();
	getTransform().setPosition(currentPos.x + 2.0f, currentPos.y - 1.6f);
	setDraw(true);*/
	
}

Enemy::Enemy(float damage_) {
	cout << "Enemy Overloaded Constructor" << endl;
	damage = damage_;
	glm::vec3 currentPos = getTransform().getPosition();
	getTransform().setPosition(currentPos.x + 2.0f, currentPos.y - 1.6f);
	setDraw(false);
	//Collider
	addColliderComponent();
	getColliderComponent()->setTrigger(true);
	getColliderComponent()->setDimension(1.0f, 1.5f);
	//getColliderComponent()->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	//getTransform().setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	setDrawCollider(true);
	//Physics

	//Attack collider
	attackCollider = new EnemyAttackCollider(5);
	attackCollider->setDraw(false);
	attackCollider->setDrawCollider(false);
	attackCollider->addColliderComponent();
	attackCollider->setActive(false);
	attackCollider->getColliderComponent()->setTrigger(true);
	attackCollider->getColliderComponent()->setDimension(1.0f, 1.0f);
	//attackCollider->getColliderComponent()->setOffset(glm::vec3(-1.1f, 0.0f, 0.0f));
}

void Enemy::selfUpdate(float dt) {
	attackTimeElapsed += dt;

	attackCollider->getTransform().setPosition(glm::vec3(getTransform().getPosition().x - 1.1f, getTransform().getPosition().y, getTransform().getPosition().z));

	if (attackTimeElapsed >= attackTimer) {
		attackTimeElapsed = 0.0f;

		if (attackCollider->getIsActive()) {
			attackCollider->setActive(false);
			attackCollider->setDrawCollider(false);
			attackCollider->resetHit();
			//cout << "Disable Enemy Collider" << endl;
		} else {
			attackCollider->setActive(true);
			attackCollider->setDrawCollider(true);
			//cout << "Enable Enemy Collider" << endl;
		}
	}
}

DrawableObject* Enemy::getEnemyAttackCollider() {
	return attackCollider;
}