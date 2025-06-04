#include "Sword.h"
#include <iostream>

// Constructor
Sword::Sword() {
    PlayerAttackCollider* lightAttack1Sword = new PlayerAttackCollider(40, 15);
    lightAttack1Sword->setName("lightAttack1Sword");
    lightAttack1Sword->setDraw(false);
    lightAttack1Sword->addColliderComponent();
    lightAttack1Sword->getColliderComponent()->setTrigger(true);
    lightAttack1Sword->getColliderComponent()->setEnableCollision(false); // Set collision to false at the start
    lightAttack1Sword->getColliderComponent()->setDimension(1.8f, 0.6f); // Set collider dimension
    lightAttack1Sword->getTransform().setPosition(glm::vec3(0.85f, -1.0f, 0.0f));
    lightAttack1Sword->setDrawCollider(false);
    chainAttackList.push_back(lightAttack1Sword);

    PlayerAttackCollider* lightAttack2Sword = new PlayerAttackCollider(40, 15);
    lightAttack2Sword->setName("lightAttack2Sword");
    lightAttack2Sword->setDraw(false);
    lightAttack2Sword->addColliderComponent();
    lightAttack2Sword->getColliderComponent()->setTrigger(true);
    lightAttack2Sword->getColliderComponent()->setEnableCollision(false); // Set collision to false at the start
    lightAttack2Sword->getColliderComponent()->setDimension(1.8f, 1.0f); // Set collider dimension
    lightAttack2Sword->getTransform().setPosition(glm::vec3(1.55f, -1.0f, 0.0f));
    lightAttack2Sword->setDrawCollider(false);
    chainAttackList.push_back(lightAttack2Sword);

    PlayerAttackCollider* lightAttack3Sword = new PlayerAttackCollider(40, 15);
    lightAttack3Sword->setName("lightAttack3Sword");
    lightAttack3Sword->setDraw(false);
    lightAttack3Sword->addColliderComponent();
    lightAttack3Sword->getColliderComponent()->setTrigger(true);
    lightAttack3Sword->getColliderComponent()->setEnableCollision(false); // Set collision to false at the start
    lightAttack3Sword->getColliderComponent()->setDimension(1.9f, 1.25f); // Set collider dimension
    lightAttack3Sword->getTransform().setPosition(glm::vec3(2.05f, -1.0f, 0.0f));
    lightAttack3Sword->setDrawCollider(false);
    chainAttackList.push_back(lightAttack3Sword);

    PlayerAttackCollider* heavyAttackSword = new PlayerAttackCollider(50, 20);
    heavyAttackSword->setName("heavyAttackSword");
    heavyAttackSword->setDraw(false);
    heavyAttackSword->addColliderComponent();
    heavyAttackSword->getColliderComponent()->setTrigger(true);
    heavyAttackSword->getColliderComponent()->setEnableCollision(false); // Set collision to false at the start
    heavyAttackSword->getColliderComponent()->setDimension(2.0f, 1.75f); // Set collider dimension
    heavyAttackSword->getTransform().setPosition(glm::vec3(2.05f, -1.0f, 0.0f));
    heavyAttackSword->setDrawCollider(false);
    chainAttackList.push_back(heavyAttackSword);

    PlayerAttackCollider* smallUltSword = new PlayerAttackCollider(350, 0);
    smallUltSword->setName("smallUltSword");
    smallUltSword->setDraw(false);
    smallUltSword->addColliderComponent();
    smallUltSword->getColliderComponent()->setTrigger(true);
    smallUltSword->getColliderComponent()->setEnableCollision(false); // Set collision to false at the start
    smallUltSword->getColliderComponent()->setDimension(5.5f, 2.5f); // Set collider dimension
    smallUltSword->setDrawCollider(false);
    chainAttackList.push_back(smallUltSword);

    PlayerAttackCollider* bigUltSword = new PlayerAttackCollider(1650, 0);
    bigUltSword->setName("bigUltSword");
    bigUltSword->setDraw(false);
    bigUltSword->addColliderComponent();
    bigUltSword->getColliderComponent()->setTrigger(true);
    bigUltSword->getColliderComponent()->setEnableCollision(false); // Set collision to false at the start
    bigUltSword->initAnimation(0, 0);
    bigUltSword->getAnimationComponent()->addState("BigUlt1", 0, 5);
    bigUltSword->getAnimationComponent()->addState("BigUlt2", 0, 5);
    bigUltSword->getAnimationComponent()->addState("BigUlt3", 0, 5);
    bigUltSword->getAnimationComponent()->addState("BigUlt4", 0, 3);
    bigUltSword->getTransform().setScale(glm::vec3(1.6f * 10, 0.9f * 10, 1));
    bigUltSword->drawLayer = 1;
    //bigUltSword->getColliderComponent()->setDimension(21.0f, 10.0f); // Set collider dimension
    bigUltSword->setDrawCollider(false);
    chainAttackList.push_back(bigUltSword);
}

// Destructor
Sword::~Sword() {
    for (auto obj : chainAttackList) {
        delete obj;
    }
}

// Update method
void Sword::update(float dt, Player* playerObject) {
    glm::vec3 playerPos = playerObject->getTransform().getPosition();

    for (auto obj : chainAttackList) {
        
        if (!canDrawCollider) {
            obj->setCanDrawColliderNew(false);
        }
        else {
            obj->setCanDrawColliderNew(true);
        }

        if (obj->getName() == "lightAttack1Sword") {
            obj->getTransform().setPosition(playerPos + attack1Offset);
            flipOffset(obj, playerObject);
        }
        else if (obj->getName() == "lightAttack2Sword") {
            obj->getTransform().setPosition(playerPos + attack2Offset);
            flipOffset(obj, playerObject);
        }
        else if (obj->getName() == "lightAttack3Sword") {
            obj->getTransform().setPosition(playerPos + attack3Offset);
            flipOffset(obj, playerObject);
        }
        else if (obj->getName() == "heavyAttackSword") {
            obj->getTransform().setPosition(playerPos + heavyAttackOffset);
            flipOffset(obj, playerObject);
        }
        else if (obj->getName() == "smallUltSword") {
            obj->getTransform().setPosition(playerPos + smallUltOffset);
            flipOffset(obj, playerObject);
        }
        /*else if (obj->getName() == "bigUltSword") {
            obj->getTransform().setPosition(playerPos + bigUltOffset);
            flipOffset(obj, playerObject);
        }*/
    }
}

// Flip offset if the player is facing the opposite direction
void Sword::flipOffset(DrawableObject* obj, Player* playerObject) {
    if (!playerObject) return;
    if (playerObject->getFacingRight()) return;

    glm::vec3 newPos = playerObject->getTransform().getPosition();

    if (obj->getName() == "lightAttack1Sword") {
        newPos.x = newPos.x - attack1Offset.x;
        newPos.y = newPos.y + attack1Offset.y;
        obj->getTransform().setPosition(newPos);
    }
    else if (obj->getName() == "lightAttack2Sword") {
        newPos.x = newPos.x - attack2Offset.x;
        newPos.y = newPos.y + attack2Offset.y;
        obj->getTransform().setPosition(newPos);
    }
    else if (obj->getName() == "lightAttack3Sword") {
        newPos.x = newPos.x - attack3Offset.x;
        newPos.y = newPos.y + attack3Offset.y;
        obj->getTransform().setPosition(newPos);
    }
    else if (obj->getName() == "heavyAttackSword") {
        newPos.x = newPos.x - heavyAttackOffset.x;
        newPos.y = newPos.y + heavyAttackOffset.y;
        obj->getTransform().setPosition(newPos);
    }
    else if (obj->getName() == "smallUltSword") {
        newPos.x = newPos.x - smallUltOffset.x;
        newPos.y = newPos.y + smallUltOffset.y;
        obj->getTransform().setPosition(newPos);
    }
    else if (obj->getName() == "bigUltSword") {
        newPos.x = newPos.x - bigUltOffset.x;
        newPos.y = newPos.y + bigUltOffset.y;
        obj->getTransform().setPosition(newPos);
    }
}

// Chain attack method (unused in your code)
void Sword::chainAttack() {
    // Not used in your current code
}

// Getter methods
std::list<DrawableObject*> Sword::getChainAttackList() const {
    return chainAttackList;
}

void Sword::setCurrentChainAttack(int i) {
    currentChainAttack = i;
}

int Sword::getCurrentChainAttack() const {
    return currentChainAttack;
}

void Sword::setInChainAttack(bool s) {
    inChainAttack = s;
}

bool Sword::getInChainAttack() const {
    return inChainAttack;
}

void Sword::setInputBuffer(bool s) {
    inputBuffer = s;
}

bool Sword::getInputBuffer() const {
    return inputBuffer;
}

DrawableObject* Sword::getChainAttackObject(int index) {
    if (index < 0 || index >= chainAttackList.size()) {
        return nullptr;
    }

    auto it = chainAttackList.begin();
    std::advance(it, index);
    return *it;
}

void Sword::setSmallUltReady(bool v) {
    smallUltReady = v;
}

bool Sword::getSmallUltReady() const {
    return smallUltReady;
}

void Sword::setBigUltReady(bool v) {
    bigUltReady = v;
}

bool Sword::getBigUltReady() const {
    return bigUltReady;
}