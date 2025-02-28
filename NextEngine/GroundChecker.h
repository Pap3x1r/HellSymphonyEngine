#pragma once
#include "SimpleObject.h"
#include <iostream>

using namespace std;

class GroundChecker : public SimpleObject {

public:
    GroundChecker();

    void onCollisionEnter(Collider* collider) override;
    void onCollisionStay(Collider* collider) override;
    void onTriggerEnter(Collider* collider) override;
    void onTriggerStay(Collider* collider) override;
};