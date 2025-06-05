#include "IceFloor.h"
#include "Lucifer.h"


IceFloor::IceFloor() {
    setName("IceFloor");

    getTransform().setPosition(glm::vec3(0, -2.125f, 0));
    getTransform().setScale(glm::vec3(16.0f, 3.0f, 1.0f));
    addColliderComponent();
    getColliderComponent()->setDimension(0.55f, 0.55f);
    getColliderComponent()->setTrigger(true);

    setDrawCollider(true);
    //setCanDrawColliderNew(true);

    initAnimation(17, 1);
    getAnimationComponent()->addState("icefloor", 0, 17);
    setTexture("../Resource/Texture/Lucifer/VFX/Ice floor.png", 1, 17, 0);
    getAnimationComponent()->setState("icefloor");

    duration = 0.08f * 17;
    hasHit = false;
    damage = 10;

    lucifer = Lucifer::getInstance();

    atk = new EnemyAttackCollider(5);
    atk->setDraw(false);
    atk->setDrawCollider(true);
    //atk->setCanDrawColliderNew(true);
    atk->addColliderComponent();
    atk->getColliderComponent()->setTrigger(true);
    atk->getColliderComponent()->setDimension(15.0f, 0.85f);
    atk->getTransform().setPosition(glm::vec3(0, -3.0f, 0));

    isActive = false;
    startUpTimer = 0.08f * 5;
    activeTimer = 0.08f * 4;
    recoveryTimer = 0.08f * 8;

    hasStarted = false;
    hasBombed = false;
}



void IceFloor::update(float dt) {

    if (hasStarted == false) {
        startUpTimer -= dt;
        if (startUpTimer <= 0) {
            hasStarted = true;
            isActive = true;
            atk->setActive(true);
            lucifer->getLevel()->addObject(atk);
        }
    }
    else {
        if (hasBombed == false) {
            activeTimer -= dt;
            if (activeTimer <= 0) {
                hasBombed = true;
                isActive = false;
                DrawableObject::destroyObject(atk);
            }
        }
    }

    if (hasStarted == true && hasBombed == true) {
        recoveryTimer -= dt;
        if (recoveryTimer <= 0) {
            
            DrawableObject::destroyObject(this);
        }
    }




}


