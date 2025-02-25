#pragma once
#include "Boss.h"
#include "ZizIdleState.h"
#include "ZizGustState.h"
#include "Gust.h"


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

    DrawableObject* createGust();

    BossStateMachine* getStateMachine() const;
    

};