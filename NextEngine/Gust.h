#pragma once
#include "DrawableObject.h"
#include "Boss.h"
#include "Player.h"
#include "Ziz.h"

class Gust : public TexturedObject {
private:
    bool isMovingRight;
    float speed;
    bool hasHitPlayer;

public:
    Gust();
    Gust(Ziz* ziz);
    void update(float dt);
    void onCollision(Player* player);
    void checkOffMap();
};
