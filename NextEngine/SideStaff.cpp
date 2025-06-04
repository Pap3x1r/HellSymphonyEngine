#include "SideStaff.h"

SideStaff::SideStaff() {

    setName("SideStaff");

    initAnimation(33, 1);
    getAnimationComponent()->addState("beamradiant", 0, 33);

    getTransform().setScale(glm::vec3(20.0f, 3.125f, 1.0f));
    getTransform().setPosition(glm::vec3(-1, -1.5, 0));

    setTexture("../Resource/Texture/Lucifer/VFX/Laser side.png", 1, 33, 0);
    getAnimationComponent()->setState("beamradiant");

    lucifer = Lucifer::getInstance();

    timer = 0.08f * 33;
    spawnLaser = 0.08f * 14;
    spawnedLaser = false;

    atk = new EnemyAttackCollider(5);
    atk->setDraw(false);
    atk->setDrawCollider(true);
    //atk->setCanDrawColliderNew(true);
    atk->addColliderComponent();
    atk->getColliderComponent()->setTrigger(true);
    atk->getColliderComponent()->setDimension(15.0f, 6.0f);
    atk->getTransform().setPosition(glm::vec3(0, -2.0f, 0));
}

void SideStaff::update(float dt) {

    if (spawnedLaser == false) {
        spawnLaser -= dt;
        if (spawnLaser <= 0) {
            atk->setActive(true);
            lucifer->getLevel()->addObject(atk);
            spawnedLaser = true;
        }
    }

    timer -= dt;
    if (timer <= 0) {
        DrawableObject::destroyObject(atk);
        DrawableObject::destroyObject(this);
    }
}