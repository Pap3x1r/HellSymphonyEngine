#include "VerticalIceBeam.h"


VerticalIceBeam::VerticalIceBeam() {


    setName("VerticalIceBeam");

    initAnimation(33, 1);
    getAnimationComponent()->addState("lasertop", 0, 33);
    

    getTransform().setScale(glm::vec3(1.0f, 1.0f, 1.0f));
    addColliderComponent();
    getColliderComponent()->setDimension(0.5f, 1.0f);

    setTexture("../Resource/Texture/Lucifer/VFX/Laser top.png", 1, 33, 0);
    getAnimationComponent()->setState("lasertop");

    isMovingRight = false;
    speed = 3.0f;
    hasHit = false;
    damage = 5;

}

VerticalIceBeam::VerticalIceBeam(bool facingRight) {

    setName("VerticalIceBeam");

    initAnimation(33, 1);
    getAnimationComponent()->addState("lasertop", 0, 33);


    getTransform().setScale(glm::vec3(1.25f, 10.0f, 1.0f));
    addColliderComponent();
    getColliderComponent()->setDimension(0.5f, 1.0f);

    setTexture("../Resource/Texture/Lucifer/VFX/Laser top.png", 1, 33, 0);
    getAnimationComponent()->setState("lasertop");

    if (facingRight) {
        getTransform().setPosition(glm::vec3(1.0f,2,0));
    }
    else {
        getTransform().setPosition(glm::vec3(-1.0f,2, 0));
    }

    isMovingRight = facingRight;
    speed = 3.0f;
    hasHit = false;
    damage = 10;
    hasDelayed = false;
    delayBeforeStart = 0.08f * 5;
    timer = 0.08f * 28;
}

void VerticalIceBeam::update(float dt) {

    if (hasDelayed == false) {
        delayBeforeStart -= dt;
        if (delayBeforeStart <= 0) {
            hasDelayed = true;
        }
    }
    else {

        timer -= dt;
        if (timer <= dt) {
            DrawableObject::destroyObject(this);
        }

        if (isMovingRight) {
            getTransform().translate(glm::vec3(speed * dt, 0, 0));  // Moving right
        }
        else {
            getTransform().translate(glm::vec3(-speed * dt, 0, 0));  // Moving left
        }
    }

    

    checkOffMap();
}

void VerticalIceBeam::onCollisionEnter(Collider* collider) {
    DrawableObject* obj = collider->getObject();
    Player* player = dynamic_cast<Player*>(obj);

    if (player) {
        //playerInside = true;

        if (player->getInvincible() || player->getIsDashing()) {
            return;
        }

        if (!hasHit) {

            if (player->getShield()->getIsBlocking()) { // is blocking
                if (player->getShield()->getIsPerfect()) { //is perfectly timed
                    cout << "Player perfect blocked" << endl;
                    player->increaseUltimateGauge(100.0f); //instant fill
                    player->setNewColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
                    player->setHitEffectStrength(1.0f);
                    hasHit = true;
                }
                else { //if blocking but not perfectly
                    cout << "Enemy Hit Player for " << damage / 2 << " damage and " << damage / 2 << "withered damage." << endl;
                    player->getHealth()->takeDamage(damage, 30);
                    player->increaseUltimateGauge(damage / 2); // increase by withered damage.
                    player->setNewColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
                    player->setHitEffectStrength(1.0f);
                    hasHit = true;
                }
            }
            else { //is not blocking
                player->startShake(0.1f, 0.0025f);
                cout << "Enemy Hit Player for " << damage << " damage." << endl;
                player->getHealth()->takeDamage(damage);
                player->setNewColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
                player->setHitEffectStrength(1.0f);
                hasHit = true;
            }
        }

    }
}

void VerticalIceBeam::onCollisionStay(Collider* collider) {
}

void VerticalIceBeam::onCollisionExit(Collider* collider) {
    DrawableObject* obj = collider->getObject();
}

void VerticalIceBeam::onTriggerEnter(Collider* collider) {

}

void VerticalIceBeam::onTriggerStay(Collider* collider) {


}

void VerticalIceBeam::onTriggerExit(Collider* collider) {
    DrawableObject* obj = collider->getObject();
    Player* player = dynamic_cast<Player*>(obj);
}

void VerticalIceBeam::checkOffMap() {
    if (getTransform().getPosition().x > 10.0f || getTransform().getPosition().x < -10.0f) {
        DrawableObject::destroyObject(this);
    }
}
