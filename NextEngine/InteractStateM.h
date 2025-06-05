#pragma once
#include <iostream>

class InteractableObject;

using namespace std;

class InteractStateM {
public:
    virtual ~InteractStateM() = default;
    virtual void enter(InteractableObject* player) = 0;
    virtual void update(InteractableObject* player, float dt) = 0;
    virtual void exit(InteractableObject* player) = 0;
};
