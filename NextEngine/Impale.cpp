#include "Impale.h"

Impale::Impale() {

}

Impale::Impale(Ziz* boss) {
	ziz = dynamic_cast<Ziz*>(boss);
	if (ziz) {
		//cout << "Found Ziz in Lightning" << endl;
	}

	setName("Impale");
	deletedAtk = false;
	hasStruck = false;
	getTransform().setScale(glm::vec3(4.0f, 8.0f, 1.0f));
	getTransform().setPosition(glm::vec3(ziz->getPlayer()->getTransform().getPosition().x, 0.5f, 0.0f));


	initAnimation(13, 1);
	getAnimationComponent()->addState("impale", 0, 11);
	setTexture("../Resource/Texture/FinalZiz/VFX/Zyzz_Impale.png", 1, 11, 0);
	getAnimationComponent()->setState("impale");
	cout << "impale Spawned" << endl;

	attackCollider = new EnemyAttackCollider(3);
	attackCollider->addColliderComponent();
	attackCollider->setDraw(false);
	attackCollider->setDrawCollider(true);
	//attackCollider->setCanDrawColliderNew(true);
	attackCollider->setActive(false);
	attackCollider->getColliderComponent()->setTrigger(true);
	attackCollider->getColliderComponent()->setDimension(0.75f, 7.0f);
	attackCollider->getTransform().setPosition(glm::vec3(getTransform().getPosition().x, -0.25f, 0.0f));

	timer = 0.08f * 11;
	attackTimer = 0.08f * 6;
	attackDurationTimer = 0.08f * 5;
	hitboxTimer = 0.08f * 2;
}



void Impale::update(float dt) {

	if (hasStruck == false && deletedAtk == false) {
		attackTimer -= dt;
		if (attackTimer <= 0) {
			SoundManager::GetInstance()->PlaySFX("Ziz_Impale");
			ziz->getLevel()->addObject(attackCollider);
			attackCollider->setActive(true);
			ziz->startShake(0.08f * 3, 0.005f);
			hasStruck = true;
		}
	}else if (hasStruck == true && deletedAtk == false) {
		attackDurationTimer -= dt;
		if (attackDurationTimer <= 0) {
			
			deletedAtk = true;
		}

		if (hitboxTimer > 0) {
			hitboxTimer -= dt;
			if (hitboxTimer <= 0) {
				DrawableObject::destroyObject(attackCollider);
			}
		}
	}



	if (timer > 0) {
		timer -= dt;
		if (timer <= 0) {
			cout << "delete impale" << endl;
			DrawableObject::destroyObject(this);
		}
	}
}