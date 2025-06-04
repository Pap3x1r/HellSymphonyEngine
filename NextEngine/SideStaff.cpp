#include "SideStaff.h"

SideStaff::SideStaff() {

    setName("SideStaff");

    initAnimation(11, 1);
    getAnimationComponent()->addState("sidestaff1", 0, 10);
    getAnimationComponent()->addState("sidestaff2", 0, 10);
    getAnimationComponent()->addState("sidestaff3", 0, 13);


    getTransform().setScale(glm::vec3(20.0f, 3.125f, 1.0f));
    getTransform().setPosition(glm::vec3(-1, -1.5, 0));

    setTexture("../Resource/Texture/Lucifer/VFX/sidelaser1.png", 1, 10, 0);
    getAnimationComponent()->setState("sidestaff1");

    lucifer = Lucifer::getInstance();

    timer = 0.08f * 33;
    spawnLaser = 0.08f * 14;
    spawnedLaser = false;


    currentAnim = 0;
    animTimer1 = 0.08f * 10;
    animTimer2 = 0.08f * 10;
    animTimer3 = 0.08f * 13;


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

    if (currentAnim == 0) {
        animTimer1 -= dt;
        if (animTimer1 <= 0) {
            setTexture("../Resource/Texture/Lucifer/VFX/sidelaser2.png", 1, 10, 0);
            getAnimationComponent()->setState("sidestaff2");
            currentAnim++;
        }
    }
    else if (currentAnim == 1) {
        animTimer2 -= dt;
        if (animTimer2 <= 0) {
            setTexture("../Resource/Texture/Lucifer/VFX/sidelaser3.png", 1, 13, 0);
            getAnimationComponent()->setState("sidestaff3");
            currentAnim++;
        }
    }else if (currentAnim == 2) {
        animTimer3 -= dt;
        if (animTimer3 <= 0) {
            currentAnim++;
        }
    }

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