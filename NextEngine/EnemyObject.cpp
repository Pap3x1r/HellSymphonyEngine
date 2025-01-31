#include "EnemyObject.h"

EnemyObject::EnemyObject() : LivingEntity(100), damage(10) {}

EnemyObject::EnemyObject(int health, int damage)
    :  LivingEntity(health), damage(damage){}

EnemyObject::~EnemyObject() {}

int EnemyObject::getDamage() const {
    return damage;
}

void EnemyObject::setDamage(int damage) {
    this->damage = damage;
}

void EnemyObject::attack(LivingEntity& target) {
    target.takeDamage(damage);
}
