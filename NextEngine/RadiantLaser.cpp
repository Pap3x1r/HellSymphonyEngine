#pragma once
#include "RadiantLaser.h"

RadiantLaser::RadiantLaser() {

    setName("RadiantLaser");

    initAnimation(20, 1);
    getAnimationComponent()->addState("radiantlaser", 0, 20);


    getTransform().setScale(glm::vec3(20.0f, 10.0f, 1.0f));
    getTransform().setPosition(glm::vec3(0.25f, 0, 0));

    setTexture("../Resource/Texture/Lucifer/VFX/laser v2.png", 1, 20, 0);
    getAnimationComponent()->setState("radiantlaser");

    lucifer = Lucifer::getInstance();

    timer = 0.08f * 20;
    spawnedAtk = false;
    delay = 0.08f * 3;

    atkCollider1 = new EnemyAttackCollider(5);
    atkCollider1->setDraw(false);
    atkCollider1->setDrawCollider(true);
    //atkCollider1->setCanDrawColliderNew(true);
    atkCollider1->addColliderComponent();
    atkCollider1->getColliderComponent()->setTrigger(true);
    atkCollider1->getColliderComponent()->setDimension(0.5f, 7.0f);
    atkCollider1->getTransform().setPosition(glm::vec3(0.07f,0,0));

    atkCollider2 = new EnemyAttackCollider(5);
    atkCollider2->setDraw(false);
    atkCollider2->setDrawCollider(true);
    //atkCollider2->setCanDrawColliderNew(true);
    atkCollider2->addColliderComponent();
    atkCollider2->getColliderComponent()->setTrigger(true);
    atkCollider2->getColliderComponent()->setDimension(2.5f, 0.15f);
    atkCollider2->getTransform().setPosition(glm::vec3(-4.75f, -2.375f, 0));


    atkCollider3 = new EnemyAttackCollider(5);
    atkCollider3->setDraw(false);
    atkCollider3->setDrawCollider(true);
    //atkCollider3->setCanDrawColliderNew(true);
    atkCollider3->addColliderComponent();
    atkCollider3->getColliderComponent()->setTrigger(true);
    atkCollider3->getColliderComponent()->setDimension(1.5f, 0.25f);
    atkCollider3->getTransform().setPosition(glm::vec3(-2.5f, -1.0f, 0));

    atkCollider4 = new EnemyAttackCollider(5);
    atkCollider4->setDraw(false);
    atkCollider4->setDrawCollider(true);
    //atkCollider4->setCanDrawColliderNew(true);
    atkCollider4->addColliderComponent();
    atkCollider4->getColliderComponent()->setTrigger(true);
    atkCollider4->getColliderComponent()->setDimension(2.5f, 0.15f);
    atkCollider4->getTransform().setPosition(glm::vec3(4.75f, -2.375f, 0));

    atkCollider5 = new EnemyAttackCollider(5);
    atkCollider5->setDraw(false);
    atkCollider5->setDrawCollider(true);
    //atkCollider5->setCanDrawColliderNew(true);
    atkCollider5->addColliderComponent();
    atkCollider5->getColliderComponent()->setTrigger(true);
    atkCollider5->getColliderComponent()->setDimension(1.5f, 0.25f);
    atkCollider5->getTransform().setPosition(glm::vec3(2.5f, -1.0f, 0));

    

}

void RadiantLaser::update(float dt) {

    if (spawnedAtk == false) {
        delay -= dt;
        if (delay <= 0) {
            spawnedAtk = true;

            atkCollider1->setActive(true);
            lucifer->getLevel()->addObject(atkCollider1);

            atkCollider2->setActive(true);
            lucifer->getLevel()->addObject(atkCollider2);

            atkCollider3->setActive(true);
            lucifer->getLevel()->addObject(atkCollider3);

            atkCollider4->setActive(true);
            lucifer->getLevel()->addObject(atkCollider4);

            atkCollider5->setActive(true);
            lucifer->getLevel()->addObject(atkCollider5);
        }
    }

    timer -= dt;
    if (timer <= 0) {
        DrawableObject::destroyObject(atkCollider1);
        DrawableObject::destroyObject(atkCollider2);
        DrawableObject::destroyObject(atkCollider3);
        DrawableObject::destroyObject(atkCollider4);
        DrawableObject::destroyObject(atkCollider5);

        DrawableObject::destroyObject(this);
    }
}