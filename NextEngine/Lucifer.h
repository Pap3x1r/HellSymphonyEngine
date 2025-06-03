#pragma once
#include "Boss.h"
#include "Enemy.h"
#include "Player.h"
#include "LuciferIdleState.h"
#include <vector>
#include <random>

class Lucifer : public Boss {
	static Lucifer* instance;

    BossStateMachine* currentState;
    Level* currentLevel;
    Health* health;
    Player* player;

    bool isInvincible;

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

};