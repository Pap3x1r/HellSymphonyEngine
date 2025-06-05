#pragma once
#include <iostream>

class Player;
class TexturedObject;

using namespace std;

class StateM {
public:
    virtual ~StateM() = default;
    virtual void enter(Player* player) = 0;
    virtual void update(Player* player, float dt) = 0;
    virtual void exit(Player* player) = 0;
};