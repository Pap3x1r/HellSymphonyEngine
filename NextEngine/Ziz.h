#pragma once
#include "Boss.h"
#include "Player.h"
#include "ZizIdleState.h"
#include "ZizGustState.h"
#include "ZizStormRiseState.h"
#include "ZizDeathState.h"
#include "Gust.h"
#include "StormRise.h"
#include "SwoopWarning.h"
#include "UltZizOnBG.h"
#include "ChompTentacle.h"
#include "Lightning.h"
#include <random>

enum zizPhase {
    none,
    firstPhase,
    secondPhase
};

class Ziz : public Boss {

private:
    static Ziz* instance;

    bool isFacingRight = true;
    bool isGrounded = true;
    bool hasTransformed = false;
    bool dead;
    bool isInvincible;

    //cam
    bool isShaking = false;
    float shakeDuration = 0.0f;
    float shakeTimer = 0.0f;
    float shakeIntensity = 15.0f; // Adjust for desired intensity
    bool shakeInterval;
    bool shakeIntervalTimer;
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<> shakeOffsetX;
    std::uniform_real_distribution<> shakeOffsetY;

    zizPhase currentPhase = zizPhase::firstPhase;
    BossStateMachine* currentState;
    Level* currentLevel;
    Health* health;
    
    Player* player;

    vector<string> texturePaths;

public:
    static Ziz* getInstance();

    Ziz();
    ~Ziz();

    void setLevel(Level* newLevel);
    Level* getLevel() const;

    void setFacingRight(bool value);
    bool getFacingRight() const;

    DrawableObject* createGust();
    DrawableObject* createStormRise();
    DrawableObject* createSwoopWarning(int side);
    DrawableObject* createChompTentacle();
    DrawableObject* createLightning();
    DrawableObject* createBGZiz();
    bool getIsInvincible();
    void setIsInvincible(bool val);

    

    BossStateMachine* getStateMachine() const;
    void facePlayer();
    void setPlayer(Player* playr);
    Player* getPlayer();

    zizPhase getPhase() const;

    void phaseChangeTracker();
    float getCurrentHealth();

    void setIdleState();
    void changePhase();
    void interruptPhaseChange();
    void interruptDeath();
    void startShake(float duration, float intensity);
    void updateShake(float deltaTime);
    void stopShake();

    void resetCam();

    Health* getHealth() const;

    

};