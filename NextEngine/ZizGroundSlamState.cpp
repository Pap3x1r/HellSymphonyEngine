#include "ZizGroundSlamState.h"
#include "SimpleObject.h"

ZizGroundSlamState* ZizGroundSlamState::instance = nullptr;

ZizGroundSlamState* ZizGroundSlamState::getInstance() {
    if (!instance) {
        instance = new ZizGroundSlamState();
    }
    return instance;
}

void ZizGroundSlamState::enter(Boss* boss) {
    ziz = dynamic_cast<Ziz*>(boss);
    if (!ziz) return;

    
    ziz->facePlayer();

    player = ziz->getPlayer();
    if (!player) return;

    // Determine slam position with offsets
    selectTarget();

    // Setup hitbox
    attackCollider = new EnemyAttackCollider(5);
    attackCollider->setDraw(false);
    attackCollider->setDrawCollider(true);
    attackCollider->addColliderComponent();
    attackCollider->setActive(false);
    //attackCollider->setCanDrawColliderNew(true);
    attackCollider->getColliderComponent()->setTrigger(true);
    attackCollider->getColliderComponent()->setDimension(1.0f, 1.0f);
    attackCollider->getTransform().setPosition(glm::vec3(player->getTransform().getPosition().x, -1.9f, 0.0f));
    ziz->getLevel()->addObject(attackCollider);

    // Phase flags
    hasStartUp = false;
    hasLaunched = false;
    peakReached = false;
    isDescending = false;
    hasImpacted = false;

    // Timers
    startupTime = 0.08f * 8;
    flyupTime = 0.08f * 5;
    hoverTime = 0.08f * 3;

    descendTime = 0.08f * 2;

    recoverTime = 0.08f * 5;

    slamTimer = 0.0f;

    ziz->setTexture("../Resource/Texture/FinalZiz/groundslam/1_Zyzz_GroundSlam_Startup.png", 1, 14, 0);
    ziz->getAnimationComponent()->setState("groundslamstartup");

    SoundManager::GetInstance()->PlaySFX("Ziz_GroundSlam");
}

void ZizGroundSlamState::update(Boss* boss, float dt) {
    if (!ziz) return;

    glm::vec3 pos = ziz->getTransform().getPosition();

    if (hasStartUp == false) {
        startupTime -= dt;
        if (startupTime <= 0) {
            hasStartUp = true;
        }
    }else if (hasLaunched == false && hasStartUp == true) {
        flyupTime -= dt;
        float t = 1.0f - (flyupTime / (8 * 0.08f));
        t = glm::clamp(t, 0.0f, 1.0f);
        pos.y = glm::mix(startupPosition.y, midairTarget.y, t);
        ziz->getTransform().setPosition(pos);

        if (flyupTime <= 0) {
            hasLaunched = true;
            //ziz->setTexture("../Resource/Texture/Ziz/Ziz_GroundslamInAir.png", 1, 6, 0);
            //ziz->getAnimationComponent()->setState("groundslaminair");
        }
    }
    // 2. Hover phase - small delay before slam
    else if (hasLaunched && !peakReached) {
        hoverTime -= dt;
        if (hoverTime <= 0) {
            peakReached = true;
            isDescending = true;
            slamStartPos = ziz->getTransform().getPosition();
            slamTimer = 0.0f;
            ziz->setTexture("../Resource/Texture/FinalZiz/groundslam/2_Zyzz_GroundSlam_Active.png", 1, 5, 0);
            ziz->getAnimationComponent()->setState("groundslamactive");
            selectTarget();
            attackCollider->getTransform().setPosition(glm::vec3(player->getTransform().getPosition().x, -1.9f, 0.0f));

        }
    }
    // 3. Slam - descend diagonally toward impact position
    else if (isDescending && !hasImpacted) {
        slamTimer += dt;
        float t = slamTimer / descendTime;
        t = glm::clamp(t, 0.0f, 1.0f);
        glm::vec3 descent = glm::mix(slamStartPos, impactPosition, t);
        ziz->getTransform().setPosition(descent);

        if (t >= 0.8f && !attackCollider->getIsActive()) {
            attackCollider->setActive(true);
            ziz->startShake(0.2f, 0.005f);
            // Optional effects: camera shake, flash, etc.
        }

        if (t >= 1.0f) {
            hasImpacted = true;
            isDescending = false;
            ziz->setTexture("../Resource/Texture/FinalZiz/groundslam/3_Zyzz_GroundSlam_Recovery_NO_Sweep.png", 1, 5, 0);
            ziz->getAnimationComponent()->setState("groundslamrecovery");
        }
    }
    // 4. Recovery after slam
    else if (hasImpacted) {
        recoverTime -= dt;
        if (recoverTime <= 0.0f) {

            if (ziz->getDistanceFromPlayer() < 3.0f) {
                if ((rand() % 2) == 0) {
                    ziz->getStateMachine()->changeState(ZizIdleState::getInstance(), ziz);
                }
                else {
                    ziz->getStateMachine()->changeState(ZizWingSpanState::getInstance(), ziz);
                }

            }
            else {
                ziz->getStateMachine()->changeState(ZizIdleState::getInstance(), ziz);

            }
            
        }
    }
}

void ZizGroundSlamState::exit(Boss* boss) {
    DrawableObject::destroyObject(attackCollider);
}

void ZizGroundSlamState::selectTarget() {
    // Determine slam position with offsets
    glm::vec3 playerPos = player->getTransform().getPosition();
    glm::vec3 zizPos = ziz->getTransform().getPosition();
    float distanceX = fabs(playerPos.x - zizPos.x);
    float slamOffset = 2.0f;
    int facing = (playerPos.x > zizPos.x) ? -1 : 1;

    if (distanceX <= 3.0f) {
        if (distanceX <= 1.0f) tooClose = wayTooClose = true;
        else tooClose = true;
    }

    impactPosition = glm::vec3(player->getTransform().getPosition().x + facing * slamOffset, -0.25f, 0.0f);
    startupPosition = zizPos;
    midairTarget = glm::vec3(zizPos.x, 2.0f, 0.0f);
    ziz->facePlayer();
}
