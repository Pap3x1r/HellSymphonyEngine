#pragma once
#include <iostream>

class Boss;

using namespace std;

class BossStateM {
public:
    virtual ~BossStateM() = default;
    virtual void enter(Boss* player) = 0;
    virtual void update(Boss* player, float dt) = 0;
    virtual void exit(Boss* player) = 0;
};