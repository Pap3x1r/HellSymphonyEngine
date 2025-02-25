#include "Gust.h"
#include "Player.h"


Gust::Gust() {
    

    setName("Gust");
    setTexture("../Resource/Texture/Tornado.png");
    getTransform().setScale(glm::vec3(2.5f, 2.5f, 1.0f));
    addColliderComponent();
    
    getColliderComponent()->setDimension(0.5f, 1.0f);
    setDrawCollider(true);
    addPhysicsComponent();
    getPhysicsComponent()->setGravity(glm::vec2(0.0f, -0.02f));
    getPhysicsComponent()->setEnableGravity(true);

    isMovingRight = true;
    speed = 2.0f;  // Adjust speed of the tornado
    hasHitPlayer = false;


    std::cout << "Gust created and moving\n";
}

Gust::Gust(Ziz* ziz) {
    isMovingRight = ziz->getFacingRight();
    speed = 10.0f;  // Adjust speed of the tornado
    hasHitPlayer = false;

    // Set initial position based on Ziz's position and facing direction
    //setPosition(ziz->getTransform().getPosition());
    // Add logic for visual representation (sprites, animations, etc.)

    cout << "Gust created and moving\n";
}

void Gust::update(float dt) {
    // Move the tornado in the direction Ziz is facing
    if (isMovingRight) {
        getTransform().translate(glm::vec3(speed * dt, 0, 0));  // Moving right
    }
    else {
        getTransform().translate(glm::vec3(-speed * dt, 0, 0));  // Moving left
    }

    // Check if it hits the player or goes off-screen
    checkOffMap();
}

void Gust::onCollision(Player* player) {
    //if (!hasHitPlayer) {
    //    // Handle damage to player here
    //    //player->takeDamage(50);  // Adjust damage value
    //    hasHitPlayer = true;
    //    std::cout << "Tornado hit the player!\n";
    //}
}

void Gust::checkOffMap() {
    if (getTransform().getPosition().x > 8.0f || getTransform().getPosition().x < -8.0f) {
        // Off-screen, delete the tornado
        cout << "Tornado went off-screen, deleting.\n";
        getColliderComponent()->setEnableCollision(false);
        
        DrawableObject::destroyObject(this);
        delete this;
    }
}
