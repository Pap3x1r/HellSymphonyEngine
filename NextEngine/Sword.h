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

    glm::vec3 attack1Offset = { 0.85f, -1.0f, 0.0f };
    glm::vec3 attack2Offset = { 1.55f, -1.0f, 0.0f };
    glm::vec3 attack3Offset = { 2.05f, -1.0f, 0.0f };
    glm::vec3 heavyAttackOffset = { 2.05f, -1.0f, 0.0f };
    glm::vec3 smallUltOffset = { -1.0f, -1.0f, 0.0f };
    glm::vec3 bigUltOffset = { 0.0f, -1.0f, 0.0f };

    std::list<DrawableObject*> chainAttackList;

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

    DrawableObject* getChainAttackObject(int index);
};
