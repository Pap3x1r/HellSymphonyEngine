#include "IceSpear.h"


IceSpear::IceSpear() {


    setName("IceSpear");
    setTexture("../Resource/Texture/Lucifer/VFX/Ice arrow.png");
    getTransform().setScale(glm::vec3(0.75f, 3.75f, 1.0f));
    addColliderComponent();
    getColliderComponent()->setDimension(1.0f, 1.0f);
    getColliderComponent()->setTrigger(true);
    

    setDrawCollider(true);
    //setCanDrawColliderNew(true);

    speed = 10.0f;
    hasHit = false;
    damage = 10;
}

IceSpear::IceSpear(FacingDirection fd) {

    setName("IceSpear");
    addColliderComponent();
    setDrawCollider(true);
    //setCanDrawColliderNew(true);

    switch (fd) {
    case FacingDirection::down:
        setTexture("../Resource/Texture/Lucifer/VFX/Ice arrow.png");
        getTransform().setScale(glm::vec3(0.75f, 3.75f, 1.0f));
        getColliderComponent()->setDimension(1.0f, 1.0f);
        facingDirection = FacingDirection::down;

        getTransform().setPosition(glm::vec3(getTransform().getPosition().x, 8.0f, 0));
        startPos = getTransform().getPosition();
        targetPos = glm::vec3(getTransform().getPosition().x, 3.5f, 0);

        //cout << "created ice spear facing down" << endl;
        break;

    case FacingDirection::right:
        setTexture("../Resource/Texture/Lucifer/VFX/Ice arrow.png");
        getTransform().setScale(glm::vec3(0.75f, 3.75f, 1.0f));
        getColliderComponent()->setDimension(1.0f, 0.5f);
        getTransform().setRotationDeg(90);
        facingDirection = FacingDirection::right;

        getTransform().setPosition(glm::vec3(-10.0f, getTransform().getPosition().y, 0));
        startPos = getTransform().getPosition();
        targetPos = glm::vec3(-7.5f, getTransform().getPosition().y, 0);

        //cout << "created ice spear facing right" << endl;
        break;

    case FacingDirection::left:
        setTexture("../Resource/Texture/Lucifer/VFX/Ice arrow.png");
        getTransform().setScale(glm::vec3(0.75f, 3.75f, 1.0f));
        getColliderComponent()->setDimension(1.0f, 0.5f);
        getTransform().setRotationDeg(-90);
        facingDirection = FacingDirection::left;

        getTransform().setPosition(glm::vec3(10.0f, getTransform().getPosition().y, 0));
        startPos = getTransform().getPosition();
        targetPos = glm::vec3(7.5f, getTransform().getPosition().y, 0);

        //cout << "created ice spear facing left" << endl;
        break;
    default:
        break;
    }



    speed = 12.0f;
    hasHit = false;
    damage = 10;

    isInPlace = false;
    prepareTimer = 1.0f;
    prepareDuration = 1.0f;

    hasLaunched = false;
    delayBeforeLaunch = 1.0f;


}

IceSpear::IceSpear(FacingDirection fd, float pos) {

    setName("IceSpear");
    addColliderComponent();
    setDrawCollider(true);
    //setCanDrawColliderNew(true);

    switch (fd) {
    case FacingDirection::down:
        setTexture("../Resource/Texture/Lucifer/VFX/Ice arrow.png");
        getTransform().setScale(glm::vec3(0.75f, 3.75f, 1.0f));
        getColliderComponent()->setDimension(1.0f, 1.0f);
        facingDirection = FacingDirection::down;

        getTransform().setPosition(glm::vec3(pos, 8.0f, 0));
        startPos = getTransform().getPosition();
        targetPos = glm::vec3(getTransform().getPosition().x, 3.5f, 0);


        //cout << "created ice spear facing down" << endl;
        break;

    case FacingDirection::right:
        setTexture("../Resource/Texture/Lucifer/VFX/Ice arrow.png");
        getTransform().setScale(glm::vec3(0.75f, 3.75f, 1.0f));
        getColliderComponent()->setDimension(2.0f, 0.25f);
        getTransform().setRotationDeg(90);
        facingDirection = FacingDirection::right;

        getTransform().setPosition(glm::vec3(-10.0f, pos, 0));
        startPos = getTransform().getPosition();
        targetPos = glm::vec3(-7.5f, getTransform().getPosition().y, 0);

        //cout << "created ice spear facing right" << endl;
        break;

    case FacingDirection::left:
        setTexture("../Resource/Texture/Lucifer/VFX/Ice arrow.png");
        getTransform().setScale(glm::vec3(0.75f, 3.75f, 1.0f));
        getColliderComponent()->setDimension(2.0f, 0.25f);
        getTransform().setRotationDeg(-90);
        facingDirection = FacingDirection::left;

        getTransform().setPosition(glm::vec3(10.0f, pos, 0));
        startPos = getTransform().getPosition();
        targetPos = glm::vec3(7.5f, getTransform().getPosition().y, 0);

        //cout << "created ice spear facing left" << endl;
        break;


    default:
        break;
    }

    

    speed = 12.0f;
    hasHit = false;
    damage = 10;

    isInPlace = false;
    prepareTimer = 1.0f;
    prepareDuration = 1.0f;

    hasLaunched = false;
    delayBeforeLaunch = 1.0f;


}

IceSpear::IceSpear(Player* playerTarget) {
    setName("IceSpear");
    addColliderComponent();
    setDrawCollider(true);

    isTracking = true;
    targetPlayer = playerTarget;

    setTexture("../Resource/Texture/Lucifer/VFX/Ice arrow.png");
    getTransform().setScale(glm::vec3(0.5f, 2.5f, 1.0f));
    getColliderComponent()->setDimension(1.0f, 0.25f);
    facingDirection = FacingDirection::tracking; // Irrelevant but required

    // Spawn from above, center-ish
    getTransform().setPosition(glm::vec3(0.0f, 8.0f, 0));
    startPos = getTransform().getPosition();
    targetPos = glm::vec3(0.0f, 3.5f, 0); // Aim point for drop-in

    speed = 17.5f;
    hasHit = false;
    damage = 10;

    isInPlace = false;
    prepareTimer = 1.0f;
    prepareDuration = 1.0f;

    hasLaunched = false;
    delayBeforeLaunch = 2.0f;
    angularVelocity = 0.0f;

    //cout << "spawn tracking spear" << endl;
}

IceSpear::IceSpear(Player* playerTarget, float pos) {
    setName("IceSpear");
    addColliderComponent();
    setDrawCollider(true);

    isTracking = true;
    targetPlayer = playerTarget;

    setTexture("../Resource/Texture/Lucifer/VFX/Ice arrow.png");
    getTransform().setScale(glm::vec3(0.5f, 2.5f, 1.0f));
    getColliderComponent()->setDimension(1.0f, 0.25f);
    facingDirection = FacingDirection::tracking; // Irrelevant but required
    getColliderComponent()->setTrigger(true);

    // Spawn from above, center-ish
    getTransform().setPosition(glm::vec3(pos, 8.0f, 0));
    startPos = getTransform().getPosition();
    targetPos = glm::vec3(pos, 3.5f, 0); // Aim point for drop-in

    speed = 17.5f;
    hasHit = false;
    damage = 5;

    isInPlace = false;
    prepareTimer = 1.0f;
    prepareDuration = 1.0f;

    hasLaunched = false;
    delayBeforeLaunch = 2.0f;
    angularVelocity = 0.0f;

    //cout << "spawn tracking spear" << endl;
}


void IceSpear::update(float dt) {

    glm::vec3 pos = getTransform().getPosition();

    if (!isInPlace) {
        prepareTimer -= dt;

        float t = 1.0f - (prepareTimer / prepareDuration);
        t = glm::clamp(t, 0.0f, 1.0f);
        pos = glm::mix(startPos, targetPos, t);

        getTransform().setPosition(pos);

        if (prepareTimer <= 0) {
            isInPlace = true;
        }
    }

    if (!hasLaunched && isInPlace) {
        if (delayBeforeLaunch > 0.0f) {
            delayBeforeLaunch -= dt;

            if (facingDirection == FacingDirection::tracking) {
                glm::vec3 playerPos = targetPlayer->getTransform().getPosition();
                glm::vec3 toPlayer = playerPos - getTransform().getPosition();

                float targetAngle = glm::degrees(atan2(toPlayer.y, toPlayer.x)) + 90.0f;

                float angleDiff = glm::mod((targetAngle - currentAngle + 540.0f), 360.0f) - 180.0f;

                // Overshoot variables
                
                float stiffness = 50.0f;   // springiness (higher = snappier)
                float damping = 8.0f;      // damping (higher = less overshoot)

                // Spring-damper physics
                angularVelocity += angleDiff * stiffness * dt;
                angularVelocity -= angularVelocity * damping * dt;
                currentAngle += angularVelocity * dt;

                getTransform().setRotationDeg(currentAngle);
            }


            if (delayBeforeLaunch <= 0.0f) {
                hasLaunched = true;
                SoundManager::GetInstance()->PlaySFX("Lucifer-Barrage_Release");
                if (facingDirection == FacingDirection::tracking) {
                    glm::vec3 playerPos = targetPlayer->getTransform().getPosition();
                    direction = glm::normalize(playerPos - getTransform().getPosition());
                }
            }
        }
    }

    // Launching phase
    if (hasLaunched) {
        switch (facingDirection) {
        case FacingDirection::down:
            getTransform().translate(glm::vec3(0, -speed * dt, 0));
            break;
        case FacingDirection::right:
            getTransform().translate(glm::vec3(speed * dt, 0, 0));
            break;
        case FacingDirection::left:
            getTransform().translate(glm::vec3(-speed * dt, 0, 0));
            break;
        case FacingDirection::tracking:
            getTransform().translate(direction * speed * dt);
            break;
        default:
            break;
        }
    }

    checkOffMap();
}


void IceSpear::onCollisionEnter(Collider* collider) {
    DrawableObject* obj = collider->getObject();
    Player* player = dynamic_cast<Player*>(obj);

    if (player) {
        //playerInside = true;

        if (player->getInvincible() || player->getIsDashing()) {
            return;
        }

        if (!hasHit) {

            if (player->getShield()->getIsBlocking()) { // is blocking
                if (player->getShield()->getIsPerfect()) { //is perfectly timed
                    cout << "Player perfect blocked" << endl;
                    player->increaseUltimateGauge(100.0f); //instant fill
                    player->setNewColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
                    player->setHitEffectStrength(1.0f);
                    hasHit = true;
                }
                else { //if blocking but not perfectly
                    cout << "Enemy Hit Player for " << damage / 2 << " damage and " << damage / 2 << "withered damage." << endl;
                    player->getHealth()->takeDamage(damage, 30);
                    player->increaseUltimateGauge(damage / 2); // increase by withered damage.
                    player->setNewColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
                    player->setHitEffectStrength(1.0f);
                    hasHit = true;
                }
            }
            else { //is not blocking
                player->startShake(0.1f, 0.0025f);
                cout << "Enemy Hit Player for " << damage << " damage." << endl;
                player->getHealth()->takeDamage(damage);
                player->setNewColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
                player->setHitEffectStrength(1.0f);
                hasHit = true;
            }
        }

    }
}

void IceSpear::onCollisionStay(Collider* collider) {
}

void IceSpear::onCollisionExit(Collider* collider) {
}

void IceSpear::onTriggerEnter(Collider* collider) {
}

void IceSpear::onTriggerStay(Collider* collider) {
}

void IceSpear::onTriggerExit(Collider* collider) {
}



void IceSpear::checkOffMap() {

    switch (facingDirection) {
    case FacingDirection::down:
        if (getTransform().getPosition().y < -8.0f) {
            DrawableObject::destroyObject(this);
        }
        break;
    case FacingDirection::right:
        if (getTransform().getPosition().x > 10.0f) {
            DrawableObject::destroyObject(this);
        }
        break;
    case FacingDirection::left:
        if (getTransform().getPosition().x < -10.0f) {
            DrawableObject::destroyObject(this);
        }
        break;
    case FacingDirection::tracking:
        if ((getTransform().getPosition().y < -8.0f) || (getTransform().getPosition().x > 10.0f) || (getTransform().getPosition().x < -10.0f)) {
            //cout << "remove tracking" << endl;
            DrawableObject::destroyObject(this);
        }
        break;
    default:
        break;
    }

}

