#include "GroundChecker.h"
#include "Player.h"

GroundChecker::GroundChecker() {
    setName("GroundChecker");
    setTag(Tag::GroundChecker);
    getTransform().setScale(glm::vec3(0.5f, 0.05f, 0.0f));
    //getTransform().setPosition(glm::vec3(0.0, 1.0f, 0.0f));
    addColliderComponent();
    getColliderComponent()->setTrigger(true);

    //Draw mode
    setDraw(false);
    setDrawCollider(true);
}

void GroundChecker::setPlayer(Player* player_) {
    player = player_;
}

void GroundChecker::onCollisionEnter(Collider* collider) {
    DrawableObject* obj = collider->getObject();

    if (obj->getName() == "Floor") {
        player->setIsGrounded(true);
    }

    //cout << "collisionEnter player hit the floor" << endl;
}

void GroundChecker::onCollisionStay(Collider* collider) {
    DrawableObject* obj = collider->getObject();

    if (obj->getName() == "Floor") {
        //player->setIsGrounded(true);
    }

    //cout << "collisionStay player hit the floor" << endl;
}

//void GroundChecker::onTriggerEnter(Collider* collider) {
//    DrawableObject* obj = collider->getObject();
//
//    if (obj->getName() == "Floor") {
//        cout << "player hit the floor" << endl;
//    }
//
//    //cout << "triggerEnter player hit the floor" << endl;
//}
//void GroundChecker::onTriggerStay(Collider* collider) {
//    DrawableObject* obj = collider->getObject();
//
//    if (obj->getName() == "Floor") {
//        cout << "player hit the floor" << endl;
//    }
//
//    //cout << "triggerStay player hit the floor" << endl;
//}