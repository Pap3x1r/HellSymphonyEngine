#pragma once
#include "Boss.h"
#include "ZizIdleState.h"


class Ziz : public Boss {

private:
    bool isFacingRight = true;
    bool isGrounded = true;

    Level* currentLevel;
    Health* health;
    BossStateMachine* currentState;


public:
    Ziz();
    ~Ziz();

    void setLevel(Level* newLevel);
    Level* getLevel() const;

    void setFacingRight(bool value);
    bool getFacingRight() const;

    BossStateMachine* getStateMachine() const;
    

};