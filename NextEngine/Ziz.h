#pragma once
#include "Boss.h"
#include "Player.h"
#include "ZizIdleState.h"
#include "ZizGustState.h"
#include "ZizStormRiseState.h"
#include "Gust.h"
#include "StormRise.h"


class Ziz : public Boss {

private:
    bool isFacingRight = true;
    bool isGrounded = true;

    Level* currentLevel;
    Health* health;
    BossStateMachine* currentState;
    Player* player;


public:
    Ziz();
    ~Ziz();

    void setLevel(Level* newLevel);
    Level* getLevel() const;

    void setFacingRight(bool value);
    bool getFacingRight() const;

    DrawableObject* createGust();
    DrawableObject* createStormRise();

    BossStateMachine* getStateMachine() const;
    void facePlayer();
    void setPlayer(Player* playr);
    Player* getPlayer();
    

};