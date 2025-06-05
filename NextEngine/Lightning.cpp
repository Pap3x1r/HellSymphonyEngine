#include "Lightning.h"

Lightning::Lightning() {

}

Lightning::Lightning(Ziz* boss) {
	ziz = dynamic_cast<Ziz*>(boss);
	if (ziz) {
		//cout << "Found Ziz in Lightning" << endl;
	}

	unsigned seed = std::chrono::system_clock::now()
		.time_since_epoch()
		.count();
	gen.seed(seed);

	randomX = std::uniform_real_distribution<>(-7.5, 7.5);
	float randomXPos = randomX(gen);
	

	setName("Lightning");
	deletedAtk = false;
	hasStruck = false;
	getTransform().setScale(glm::vec3(4.0f, 8.0f, 1.0f));
	getTransform().setPosition(glm::vec3(randomXPos, 0.5f, 0.0f));


	initAnimation(13, 1);
	getAnimationComponent()->addState("thunder", 0, 13);
	setTexture("../Resource/Texture/FinalZiz/VFX/lightning effect.png", 1, 13, 0);
	getAnimationComponent()->setState("thunder");
	//cout << "Lightning Spawned" << endl;

	attackCollider = new EnemyAttackCollider(3);
	attackCollider->addColliderComponent();
	attackCollider->setDraw(false);
	attackCollider->setDrawCollider(true);
	//attackCollider->setCanDrawColliderNew(true);
	attackCollider->setActive(false);
	attackCollider->getColliderComponent()->setTrigger(true);
	attackCollider->getColliderComponent()->setDimension(1.5f, 3.0f);
	attackCollider->getTransform().setPosition(glm::vec3(getTransform().getPosition().x, -1.25f, 0.0f));

	timer = 0.08 * 13;
	attackTimer = 0.08 * 8;
	attackDurationTimer = 0.08 * 2;
}

Lightning::Lightning(Ziz* boss, float x) {
	ziz = dynamic_cast<Ziz*>(boss);
	if (ziz) {
		//cout << "Found Ziz in Lightning" << endl;
	}


	setName("Lightning");
	deletedAtk = false;
	hasStruck = false;
	getTransform().setScale(glm::vec3(4.0f, 8.0f, 1.0f));
	getTransform().setPosition(glm::vec3(x, 0.5f, 0.0f));


	initAnimation(13, 1);
	getAnimationComponent()->addState("thunder", 0, 13);
	setTexture("../Resource/Texture/FinalZiz/VFX/lightning effect.png", 1, 13, 0);
	getAnimationComponent()->setState("thunder");
	//cout << "Lightning Spawned" << endl;

	attackCollider = new EnemyAttackCollider(3);
	attackCollider->addColliderComponent();
	attackCollider->setDraw(false);
	attackCollider->setDrawCollider(true);
	//attackCollider->setCanDrawColliderNew(true);
	attackCollider->setActive(false);
	attackCollider->getColliderComponent()->setTrigger(true);
	attackCollider->getColliderComponent()->setDimension(1.5f, 3.0f);
	attackCollider->getTransform().setPosition(glm::vec3(getTransform().getPosition().x, -1.25f, 0.0f));

	timer = 0.08 * 13;
	attackTimer = 0.08 * 8;
	attackDurationTimer = 0.08 * 2;
}


void Lightning::update(float dt) {

	if (hasStruck == false) {
		attackTimer -= dt;
		if (attackTimer <= 0) {
			SoundManager::GetInstance()->PlaySFX("Ziz_Lightning");
			ziz->getLevel()->addObject(attackCollider);
			attackCollider->setActive(true);
			ziz->startShake(0.08f * 3, 0.005f);
			hasStruck = true;
		}
	}

	if (hasStruck == true && deletedAtk == false) {
		attackDurationTimer -= dt;
		if (attackDurationTimer <= 0) {
			DrawableObject::destroyObject(attackCollider);
			deletedAtk = true;
		}
	}



	if (timer > 0) {
		timer -= dt;
		if (timer <= 0) {
			cout << "delete lightinng" << endl;
			DrawableObject::destroyObject(this);
		}
	}
}