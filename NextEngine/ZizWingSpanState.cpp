#include "ZizWingSpanState.h"

ZizWingSpanState* ZizWingSpanState::instance = nullptr;

ZizWingSpanState* ZizWingSpanState::getInstance() {
	if (!instance) {
		instance = new ZizWingSpanState;
	}

	return instance;
}


void ZizWingSpanState::enter(Boss* boss) {
	ziz = dynamic_cast<Ziz*>(boss);
	if (!ziz) return;


	ziz->setTexture("../Resource/Ziz/WingSpan_1.png");
	ziz->setTexture("../Resource/Texture/FinalZiz/Zyzz_WingSweep-Sheet.png", 1, 22, 0);
	ziz->getAnimationComponent()->setState("wingspan");
	ziz->facePlayer();


	isCurling = false;
	isAttacking = false;
	hasAttacked = false;


	startupTimer = 0.08f * 12;
	activeTimer = 0.08f * 4;
	recoveryTimer = 0.08f * 6;

	attackCollider = new EnemyAttackCollider(5);
	attackCollider->setDraw(false);
	attackCollider->setDrawCollider(true);
	attackCollider->addColliderComponent();
	attackCollider->setActive(false);
	attackCollider->getColliderComponent()->setTrigger(true);
	attackCollider->getColliderComponent()->setDimension(6.5f, 3.0f);
	attackCollider->getTransform().setPosition(glm::vec3(ziz->getTransform().getPosition().x, ziz->getTransform().getPosition().y - 1.5f, 0.0f));

	ziz->getLevel()->addObject(attackCollider);


	//cout << "Ziz entered wing span" << endl;
}
	
void ZizWingSpanState::update(Boss* boss, float dt) {
	if (ziz) {
        if (!isCurling && !hasAttacked) {

            startupTimer -= dt;
            if (startupTimer <= 0) {
                isCurling = true;
                //ziz->setTexture("../Resource/Ziz/WingSpan_2.png");
				attackCollider->setActive(true);
            }
        }
        else if (isCurling && !hasAttacked) {

            activeTimer -= dt;
            if (activeTimer <= 0) {
                hasAttacked = true;
                //ziz->setTexture("../Resource/Ziz/WingSpan_3.png");
                // If attack collider is needed, activate it here
            }
        }
        else if (hasAttacked) {

            recoveryTimer -= dt;
            if (recoveryTimer <= 0) {
                ziz->getStateMachine()->changeState(ZizIdleState::getInstance(), ziz);
            }
        }
	}
}

void ZizWingSpanState::exit(Boss* boss) {
	DrawableObject::destroyObject(attackCollider);
}