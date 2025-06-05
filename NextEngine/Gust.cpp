#include "Gust.h"
#include "Ziz.h"


Gust::Gust() {
   

    setName("Gust");
    setTexture("../Resource/Texture/Ziz_Aircutter.png");
    getTransform().setScale(glm::vec3(2.5f, 2.5f, 1.0f));
    addColliderComponent();
    
    getColliderComponent()->setDimension(0.5f, 1.0f);
    
    addPhysicsComponent();
    getPhysicsComponent()->setGravity(glm::vec2(0.0f, -0.02f));
    getPhysicsComponent()->setEnableGravity(true);

    isMovingRight = false;
    speed = 3.0f;  // Adjust speed of the tornado
    hasHit = false;
    damage = 5;



    std::cout << "Gust test created and moving\n";
}

Gust::Gust(bool facingRight) {

    isMovingRight = facingRight;
    speed = 8.0f; 
    hasHit = false;
    damage = 5;
}

void Gust::update(float dt) {
    // Move the tornado in the direction Ziz is facing
    if (isMovingRight) {
        getTransform().translate(glm::vec3(speed * dt, 0, 0));  // Moving right
    }
    else {
        getTransform().translate(glm::vec3(-speed * dt, 0, 0));  // Moving left
    }
    //cout << "Gust Updating\n";
    // Check if it hits the player or goes off-screen
    checkOffMap();
}

void Gust::onCollisionEnter(Collider* collider) {
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
                cout << "Enemy Hit Player for " << damage << " damage." << endl;
                player->getHealth()->takeDamage(damage);
                player->setNewColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
                player->setHitEffectStrength(1.0f);
                hasHit = true;
            }
        }
    }
}

void Gust::onCollisionStay(Collider* collider) {
}

void Gust::onCollisionExit(Collider* collider) {
    DrawableObject* obj = collider->getObject();
}

void Gust::onTriggerEnter(Collider* collider) {
    
}

void Gust::onTriggerStay(Collider* collider) {


}

void Gust::onTriggerExit(Collider* collider) {
    DrawableObject* obj = collider->getObject();
    Player* player = dynamic_cast<Player*>(obj);
}

//void Gust::onCollision(Collider* collider) {
//    //if (!hasHitPlayer) {
//    //    // Handle damage to player here
//    //    //player->takeDamage(50);  // Adjust damage value
//    //    hasHitPlayer = true;
//    //    std::cout << "Tornado hit the player!\n";
//    //}
//}

void Gust::checkOffMap() {
    if (getTransform().getPosition().x > 8.0f || getTransform().getPosition().x < -8.0f) {
        // Off-screen, delete the tornado
        cout << "Tornado went off-screen, deleting.\n";
        
        DrawableObject::destroyObject(this);
        //delete this;
    }
}
