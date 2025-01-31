#pragma once
#include "LivingEntity.h"
#include <string>

class EnemyObject : public LivingEntity {
private:
    int damage;

public:
    EnemyObject();
    EnemyObject(int health, int damage);
    ~EnemyObject();

    int getDamage() const;
    void setDamage(int damage);

    void attack(LivingEntity& target);
};
