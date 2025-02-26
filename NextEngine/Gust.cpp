#include "Gust.h"


Gust::Gust() {
   

    setName("Gust");
    setTexture("../Resource/Ziz/Tornado.png");
    getTransform().setScale(glm::vec3(2.5f, 2.5f, 1.0f));
    addColliderComponent();
    
    getColliderComponent()->setDimension(0.5f, 1.0f);
    setDrawCollider(true);
    addPhysicsComponent();
    getPhysicsComponent()->setGravity(glm::vec2(0.0f, -0.02f));
    getPhysicsComponent()->setEnableGravity(true);

    isMovingRight = false;
    speed = 3.0f;  // Adjust speed of the tornado
    hasHit = false;
    damage = 10;
    


    std::cout << "Gust test created and moving\n";
}

Gust::Gust(bool facingRight) {
  


    isMovingRight = facingRight;
    speed = 3.0f;  // Adjust speed of the tornado
    hasHit = false;
    damage = 10;


    cout << "Gust from Ziz created and moving\n";
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
        cout << "onCollisionEnter fired" << endl;
        //playerInside = true;
        if (!hasHit) {

            if (player->getShield()->getIsBlocking()) { // is blocking
                if (player->getShield()->getIsPerfect()) { //is perfectly timed
                    cout << "Player perfect blocked" << endl;
                    player->increaseUltimateGauge(100.0f); //instant fill
                    hasHit = true;
                }
                else { //if blocking but not perfectly
                    cout << "Enemy Hit Player for " << damage / 2 << " damage and " << damage / 2 << "withered damage." << endl;
                    player->increaseUltimateGauge(damage / 2); // increase by withered damage.
                    hasHit = true;
                }
            }
            else { //is not blocking
                cout << "Enemy Hit Player for " << damage << " damage." << endl;
                hasHit = true;
            }
            DrawableObject::destroyObject(this);
        }
    }
}

void Gust::onCollisionStay(Collider* collider) {
    DrawableObject* obj = collider->getObject();
    Player* player = dynamic_cast<Player*>(obj);

    if (player) {
        
        //playerInside = true;
        if (!hasHit) {

            if (player->getShield()->getIsBlocking()) { // is blocking
                if (player->getShield()->getIsPerfect()) { //is perfectly timed
                    cout << "Player perfect blocked" << endl;
                    player->increaseUltimateGauge(100.0f); //instant fill
                    hasHit = true;
                }
                else { //if blocking but not perfectly
                    cout << "Enemy Hit Player for " << damage / 2 << " damage and " << damage / 2 << "withered damage." << endl;
                    player->increaseUltimateGauge(damage / 2); // increase by withered damage.
                    hasHit = true;
                }
            }
            else { //is not blocking
                cout << "Enemy Hit Player for " << damage << " damage." << endl;
                hasHit = true;
            }
            DrawableObject::destroyObject(this);
        }

    }
}

void Gust::onCollisionExit(Collider* collider) {
    DrawableObject* obj = collider->getObject();
}

void Gust::onTriggerEnter(Collider* collider) {
    DrawableObject* obj = collider->getObject();
    Player* player = dynamic_cast<Player*>(obj);

    if (player) {
        cout << "onTriggerEnter fired" << endl;
        //playerInside = true;
        if (!hasHit) {

            if (player->getShield()->getIsBlocking()) { // is blocking
                if (player->getShield()->getIsPerfect()) { //is perfectly timed
                    cout << "Player perfect blocked" << endl;
                    player->increaseUltimateGauge(100.0f); //instant fill
                    hasHit = true;
                }
                else { //if blocking but not perfectly
                    cout << "Enemy Hit Player for " << damage / 2 << " damage and " << damage / 2 << "withered damage." << endl;
                    player->increaseUltimateGauge(damage / 2); // increase by withered damage.
                    hasHit = true;
                }
            }
            else { //is not blocking
                cout << "Enemy Hit Player for " << damage << " damage." << endl;
                hasHit = true;
            }
            DrawableObject::destroyObject(this);
        }
    }
}

void Gust::onTriggerStay(Collider* collider) {
    DrawableObject* obj = collider->getObject();

    Player* player = dynamic_cast<Player*>(obj);

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
    if (getTransform().getPosition().x > 6.0f || getTransform().getPosition().x < -8.0f) {
        // Off-screen, delete the tornado
        cout << "Tornado went off-screen, deleting.\n";
        getColliderComponent()->setEnableCollision(false);
        
        DrawableObject::destroyObject(this);
        //delete this;
    }
}
