#pragma once
#include "SimpleObject.h"
#include <iostream>

using namespace std;

class Player;

class GroundChecker : public SimpleObject {
    Player* player;
public:
    GroundChecker();

    void setPlayer(Player* player_);

    void onCollisionEnter(Collider* collider) override;
    void onCollisionStay(Collider* collider) override;
    /*void onTriggerEnter(Collider* collider) override;
    void onTriggerStay(Collider* collider) override;*/
};