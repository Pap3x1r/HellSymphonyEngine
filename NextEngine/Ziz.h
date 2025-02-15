#pragma once
#include "TexturedObject.h"
#include "Health.h"
#include "StateMachine.h"


class Ziz : public TexturedObject {

private:
    float movementSpeed = 10.0f;
    float jumpingPower = 16.0f;

    bool isFacingRight = true;
    bool isGrounded = true;

    Level* currentLevel;
    Health* health;
    StateMachine* currentState;

public:
	Ziz();
    ~Ziz();

    void setLevel(Level* newLevel);
    Level* getLevel() const;

    void setFacingRight(bool value);
    bool getFacingRight() const;

    StateMachine* getStateMachine() const;
    

};