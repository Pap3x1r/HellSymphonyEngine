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
	activeTimer = 0.08f * 2;
	recoveryTimer = 0.08f * 8;

	attackCollider = new EnemyAttackCollider(5,30.0f, 0.25f);
	attackCollider->setDraw(false);
	attackCollider->setDrawCollider(true);
	//attackCollider->setCanDrawColliderNew(true);
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
				SoundManager::GetInstance()->PlaySFX("Ziz_WingSweep");
                isCurling = true;
                //ziz->setTexture("../Resource/Ziz/WingSpan_2.png");
				attackCollider->setActive(true);
				ziz->startShake(0.1f, 0.01f);
            }
        }
        else if (isCurling && !hasAttacked) {

            activeTimer -= dt;
            if (activeTimer <= 0) {
                hasAttacked = true;
				DrawableObject::destroyObject(attackCollider);
                //ziz->setTexture("../Resource/Ziz/WingSpan_3.png");
                // If attack collider is needed, activate it here
            }
        }
        else if (hasAttacked) {

            recoveryTimer -= dt;
            if (recoveryTimer <= 0) {
				if (ziz->getDistanceFromPlayer() < 3.0f) {
					ziz->getStateMachine()->changeState(ZizIdleState::getInstance(), ziz);

				}
				else {
					ziz->getStateMachine()->changeState(ZizIdleState::getInstance(), ziz);
				}
            }
        }
	}
}

void ZizWingSpanState::exit(Boss* boss) {
	//DrawableObject::destroyObject(attackCollider);
}