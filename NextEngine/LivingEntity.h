#pragma once
#include "TexturedObject.h"
#include <list>

class LivingEntity : public TexturedObject {
private:
    struct status;

    int health;
    bool isDead;
    std::list<status> statusList;

public:
    enum statusType {
        stun,
        wet,
        moodeng
    };
    struct status {
        status(statusType type, int cooldown);
        statusType type;
        int cooldown;
    };

    LivingEntity();
    LivingEntity(int hp);

    void setHP(int hp);
    int getHP();
    bool getIsDead();
    void addStatus(status add);
    bool findStatus(status find);
    std::list<status> getStatusList();
    void appliedStatus();
    void takeDamage(int damage);
};