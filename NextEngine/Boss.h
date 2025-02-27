#pragma once
#include "TexturedObject.h"
#include "Health.h"
#include "BossStateMachine.h"
#include "Enemy.h"


class Boss : public Enemy {//abstract

private:

    bool isFacingRight = true;
    bool isGrounded = true;

    Level* currentLevel;
    Health* health;
    BossStateMachine* currentState;

public:
    Boss();
    ~Boss();

    void setLevel(Level* newLevel);
    Level* getLevel() const;

    virtual void setFacingRight(bool value) = 0;
    bool getFacingRight() const;

    BossStateMachine* getStateMachine() const;

};