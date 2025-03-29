#pragma once
#include "Boss.h"
#include "Player.h"
#include "ZizIdleState.h"
#include "ZizGustState.h"
#include "ZizStormRiseState.h"
#include "Gust.h"
#include "StormRise.h"
#include "SwoopWarning.h"

enum zizPhase {
    none,
    firstPhase,
    secondPhase
};

class Ziz : public Boss {

private:
    bool isFacingRight = true;
    bool isGrounded = true;
    

    zizPhase currentPhase = zizPhase::firstPhase;

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
    DrawableObject* createSwoopWarning(int side);

    BossStateMachine* getStateMachine() const;
    void facePlayer();
    void setPlayer(Player* playr);
    Player* getPlayer();

    zizPhase getPhase() const;

    void phaseChangeTracker();
    float getCurrentHealth();

    void setIdleState();

    

};