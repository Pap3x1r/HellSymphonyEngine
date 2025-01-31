#include "PlayerObject.h"

PlayerObject::PlayerObject() : LivingEntity(), damage(10) {}

PlayerObject::PlayerObject(std::string name, int health, int damage)
    : LivingEntity(health), damage(damage) {}

PlayerObject::~PlayerObject() {}


int PlayerObject::getDamage() const {
    return damage;
}

void PlayerObject::setDamage(int damage) {
    this->damage = damage;
}

void PlayerObject::attack(LivingEntity& target) {
    target.takeDamage(damage);
}
