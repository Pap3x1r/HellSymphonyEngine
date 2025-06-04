#pragma once
#include "Boss.h"
#include "Enemy.h"
#include "Player.h"
#include "LuciferIdleState.h"
#include "IceSpear.h"
#include <vector>
#include <random>
#include "QTEButtonUI.h"

class Lucifer : public Boss {
	static Lucifer* instance;

    BossStateMachine* currentState;
    Level* currentLevel;
    Health* health;
    Player* player;

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

    //qte
    bool qteMode;
    bool qteInputReceieved;
    int QTETarget;
    int QTEInput;
    bool QTECorrect;

    vector<string> texturePaths;
public:
    static Lucifer* getInstance();

    Lucifer();
    ~Lucifer();

    void setLevel(Level* newLevel);
    Level* getLevel() const;
    void update(float dt);
    void setFacingRight(bool value);
    BossStateMachine* getStateMachine() const;
    void setPlayer(Player* playr);
    Player* getPlayer();
    Health* getHealth() const;

    bool getIsInvincible();
    void setIsInvincible(bool val);

    void startShake(float duration, float intensity);
    void updateShake(float deltaTime);
    void stopShake();
    void resetCam();

    IceSpear* createIceSpear(FacingDirection fd);

    //qte
    void updateQTEMode(float dt);

    bool getQTECorrect();
    bool getQTEMode();
    bool getQTEInputReceieved();
    void handleQTEInput(int input);
    void startQTEMode(int target);
    void endQTEMode();

    QTEButtonUI* createQTEButtonUI();

};