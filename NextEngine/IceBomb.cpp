#include "IceBomb.h"
#include "Lucifer.h"


IceBomb::IceBomb() {
    setName("IceBomb");

    getTransform().setPosition(glm::vec3(0,-2.75,0));
    getTransform().setScale(glm::vec3(2.0f, 2.0f, 1.0f));
    addColliderComponent();
    getColliderComponent()->setDimension(0.55f, 0.55f);
    getColliderComponent()->setTrigger(true);

    setDrawCollider(true);
    //setCanDrawColliderNew(true);

    initAnimation(13, 1);
    getAnimationComponent()->addState("icebomb", 0, 13);
    setTexture("../Resource/Texture/Lucifer/VFX/ice bomb.png", 1, 13, 0);
    getAnimationComponent()->setState("icebomb");

    duration = 0.08f * 13;
    hasHit = false;
    damage = 10;

    isActive = false;
    startUpTimer = 0.08f * 6;
    activeTimer = 0.08f * 3;
    recoveryTimer = 0.08f * 4;

    hasStarted = false;
    hasBombed = false;
}

IceBomb::IceBomb(float pos) {
    setName("IceBomb");

    getTransform().setPosition(glm::vec3(pos, -2.65, 0));
    getTransform().setScale(glm::vec3(2.0f, 2.0f, 1.0f));
    addColliderComponent();
    getColliderComponent()->setDimension(0.55f, 0.55f);
    getColliderComponent()->setTrigger(true);

    setDrawCollider(true);
    //setCanDrawColliderNew(true);

    initAnimation(13, 1);
    getAnimationComponent()->addState("icebomb", 0, 13);
    setTexture("../Resource/Texture/Lucifer/VFX/ice bomb.png", 1, 13, 0);
    getAnimationComponent()->setState("icebomb");

    duration = 0.08f * 13;
    hasHit = false;
    damage = 10;

    isActive = false;
    startUpTimer = 0.08f * 6;
    activeTimer = 0.08f * 3;
    recoveryTimer = 0.08f * 4;

    hasStarted = false;
    hasBombed = false;
}



void IceBomb::update(float dt) {

    if (hasStarted == false){
        startUpTimer -= dt;
        if (startUpTimer <= 0) {
            hasStarted = true;
            isActive = true;
        }
    }
    else {
        if (hasBombed == false) {
            activeTimer -= dt;
            if (activeTimer <= 0) {
                SoundManager::GetInstance()->PlaySFX("Lucifer_SequenceExplosion");
                hasBombed = true;
                isActive = false;
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

void IceBomb::onCollisionEnter(Collider* collider) {
    
}

void IceBomb::onCollisionStay(Collider* collider) {
    DrawableObject* obj = collider->getObject();
    Player* player = dynamic_cast<Player*>(obj);

    if (player) {
        //playerInside = true;

        if (player->getInvincible() || player->getIsDashing()) {
            return;
        }

        if (!hasHit && isActive) {



            if (player->getShield()->getIsBlocking()) { // is blocking
                if (player->getShield()->getIsPerfect()) { //is perfectly timed
                    cout << "Player perfect blocked" << endl;
                    player->increaseUltimateGauge(100.0f); //instant fill
                    player->setNewColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
                    player->setHitEffectStrength(1.0f);
                    hasHit = true;
                    SoundManager::GetInstance()->PlaySFX("Dante-Shield_BlockPerfect");
                }
                else { //if blocking but not perfectly
                    
                    cout << "Enemy Hit Player for " << damage / 2 << " damage and " << damage / 2 << "withered damage." << endl;
                    player->getHealth()->takeDamage(damage, 30);
                    player->increaseUltimateGauge(damage / 2); // increase by withered damage.
                    player->setNewColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
                    player->setHitEffectStrength(1.0f);
                    hasHit = true;
                    SoundManager::GetInstance()->PlaySFX("Dante-Shield_Block");
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

void IceBomb::onCollisionExit(Collider* collider) {

}

void IceBomb::onTriggerEnter(Collider* collider) {

}

void IceBomb::onTriggerStay(Collider* collider) {
    
}

void IceBomb::onTriggerExit(Collider* collider) {

}

//void Gust::onCollision(Collider* collider) {
//    //if (!hasHitPlayer) {
//    //    // Handle damage to player here
//    //    //player->takeDamage(50);  // Adjust damage value
//    //    hasHitPlayer = true;
//    //    std::cout << "Tornado hit the player!\n";
//    //}
//}

