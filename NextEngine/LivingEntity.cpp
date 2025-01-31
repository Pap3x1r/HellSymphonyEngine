#include "LivingEntity.h"

LivingEntity::status::status(statusType type, int cooldown) {
    this->type = type;
    this->cooldown = cooldown;
}

LivingEntity::LivingEntity() : health(100), isDead(false) {}

LivingEntity::LivingEntity(int hp) : health(hp), isDead(false) {}

void LivingEntity::setHP(int hp) {
    this->health = hp;
}

int LivingEntity::getHP() {
    return health;
}

bool LivingEntity::getIsDead() {
    return isDead;
}

void LivingEntity::addStatus(status add) {
    statusList.push_back(add);
}

bool LivingEntity::findStatus(status find) {
    for (status tus : statusList) {
        if (tus.type == find.type) {
            return true;
        }
    }
    return false;
}

std::list<LivingEntity::status> LivingEntity::getStatusList() {
    return statusList;
}

void LivingEntity::appliedStatus() {
    // Placeholder for status application logic
}

void LivingEntity::takeDamage(int damage) {
    health -= damage;
    if (health <= 0) {
        health = 0;
        isDead = true;
    }
}
