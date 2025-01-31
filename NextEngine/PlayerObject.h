#pragma once

#include "LivingEntity.h"
#include <string>

class PlayerObject : public LivingEntity {
private:
    int damage; 

public:
    PlayerObject();
    PlayerObject(std::string name, int health, int damage);
    ~PlayerObject();

    int getDamage() const;
    void setDamage(int damage);

    void attack(LivingEntity& target);
};
