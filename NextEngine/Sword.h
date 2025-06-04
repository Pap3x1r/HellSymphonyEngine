#pragma once
#include <list>
//#include "Player.h"
#include "PlayerAttackCollider.h"

class Sword {
private:
    int currentChainAttack = 0;
    int maxChainAttack = 5;

    float attackTimeElapsed = 0.0f;
    float attackTimeWindow = 0.5f;

    bool inChainAttack = false;
    bool inputBuffer = false;

    glm::vec3 attack1Offset = { 1.35f, -0.65f, 0.0f };
    glm::vec3 attack2Offset = { 1.35f, -0.5f, 0.0f };
    glm::vec3 attack3Offset = { 1.4f, -0.75f, 0.0f };
    glm::vec3 heavyAttackOffset = { 1.0f, -0.75f, 0.0f };
    glm::vec3 smallUltOffset = { -1.0f, -1.5f, 0.0f };
    glm::vec3 bigUltOffset = { 0.0f, 0.0f, 0.0f };

    std::list<DrawableObject*> chainAttackList;

    bool canDrawCollider = false;

    bool smallUltReady = true;
    bool bigUltReady = true;

public:
    // Constructor and Destructor
    Sword();
    ~Sword();

    // Public Methods
    void update(float dt, Player* playerObject);
    void flipOffset(DrawableObject* obj, Player* playerObject);
    void chainAttack();
    std::list<DrawableObject*> getChainAttackList() const;

    void setCurrentChainAttack(int i);
    int getCurrentChainAttack() const;

    void setInChainAttack(bool s);
    bool getInChainAttack() const;

    void setInputBuffer(bool s);
    bool getInputBuffer() const;

    bool* getCanDrawColliderAddress() {
        return &canDrawCollider;
    }

    DrawableObject* getChainAttackObject(int index);

    void setSmallUltReady(bool v);
    bool getSmallUltReady() const;

    void setBigUltReady(bool v);
    bool getBigUltReady() const;
};
