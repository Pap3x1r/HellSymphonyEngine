#include "PlayerBowState.h"
#include "Player.h"
#include "Bow.h"
#include "Level.h"

PlayerLightBowAttack* PlayerLightBowAttack::instance = nullptr;
PlayerHeavyBowAttack* PlayerHeavyBowAttack::instance = nullptr;
PlayerSmallBowUlt* PlayerSmallBowUlt::instance = nullptr;
PlayerBigBowUlt* PlayerBigBowUlt::instance = nullptr;

//Bow Light Attack
void PlayerLightBowAttack::enter(Player* player) {
    //cout << "Player enters Bow Light Attack state.\n";
    player->setTexture("../Resource/Texture/Dante/DanteBow/dante_lightAttack_bow.png", 1, 7, 0); //set new texture ("path", row, column)
    player->getAnimationComponent()->setState("lightAttackBow");
    currentPhase = STARTUP; //reset back to startup
    time = 0.0f;
    player->getBow()->setIsShooting(true);
    player->getPhysicsComponent()->setVelocity(glm::vec2(0.0f, player->getPhysicsComponent()->getVelocity().y));
}

void PlayerLightBowAttack::update(Player* player, float dt_) {
    time += dt_;
    //cout << "Player Idle State: " << time << " (total dt)\n";

    switch (currentPhase) {
    case STARTUP:
        //do something
        //change phase
        if (time >= 0.333f) { //this might need to change idk how to calculate dt to real time / frame lol
            currentPhase = ACTIVE;
            time = 0;
        }
        break;
    case ACTIVE:
        //do something
        //change phase
        if (time >= 0.0f) {
            currentPhase = RECOVERY;
            time = 0;
            SoundManager::GetInstance()->PlaySFX("Dante-Bow_LightAttack");
            DrawableObject* newArrow = player->getBow()->arrowShot(40, 30, player, 25); //Change damage and ult gain percentage here
            player->getLevel()->addObject(newArrow);
        }
        break;
    case RECOVERY:
        //do something
        //return to idle
        if (time >= 0.083f) {
            player->getStateMachine()->changeState(PlayerIdleState::getInstance(), player);
        }
        break;
    };

    /*if (time > 0.12f) {
        player->getAnimationComponent()->updateCurrentState();
        time = 0;
    }*/
}

void PlayerLightBowAttack::exit(Player* player) {
    //cout << "Player exits Bow Light Attack state.\n";
    player->getBow()->setIsShooting(false);
}

//Bow Heavy Attack
void PlayerHeavyBowAttack::enter(Player* player) {
    //cout << "Player enters Bow Heavy Attack state.\n";
    player->setTexture("../Resource/Texture/Dante/DanteBow/dante_heavyAttack_bow.png", 1, 16, 0);
    player->getAnimationComponent()->setState("heavyAttackBow");
    currentPhase = STARTUP;
    time = 0.0f;
    player->getBow()->setIsShooting(true);
    player->getPhysicsComponent()->setVelocity(glm::vec2(0.0f, player->getPhysicsComponent()->getVelocity().y));
    SoundManager::GetInstance()->PlaySFX("Dante-Bow_HeavyAttack");
}

void PlayerHeavyBowAttack::update(Player* player, float dt_) {
    time += dt_;
    //cout << "Player Idle State: " << time << " (total dt)\n";

    switch (currentPhase) {
    case STARTUP:
        //do something
        //change phase
        if (time >= 1.0f) {
            currentPhase = ACTIVE;
            time = 0;
        }
        break;
    case ACTIVE:
        //do something
        //change phase
        if (time >= 0.0f) {
            currentPhase = RECOVERY;
            time = 0;
            DrawableObject* newArrow = player->getBow()->arrowShot(75, 50, player, 75, 50); //Change damage and ult gain percentage here
            player->getLevel()->addObject(newArrow);
        }
        break;
    case RECOVERY:
        //do something
        //return to idle
        if (time >= 0.333f) {
            player->getStateMachine()->changeState(PlayerIdleState::getInstance(), player);
        }
        break;
    };

    /*if (time > 0.12f) {
        player->getAnimationComponent()->updateCurrentState();
        time = 0;
    }*/
}

void PlayerHeavyBowAttack::exit(Player* player) {
    //cout << "Player exits Bow Heavy Attack state.\n";
    player->getBow()->setIsShooting(false);
}

//Bow Small Ult
void PlayerSmallBowUlt::enter(Player* player) {
    //cout << "Player enters Bow Small Ult state.\n";
    player->setTexture("../Resource/Texture/Dante/DanteBow/dante_smallUlt_bow.png", 1, 13, 0);
    player->getAnimationComponent()->setState("smallUltBow");
    currentPhase = STARTUP;
    time = 0.0f;
    player->getBow()->setIsShooting(true);
    player->getPhysicsComponent()->setVelocity(glm::vec2(0.0f, player->getPhysicsComponent()->getVelocity().y));

    player->getBow()->setSmallUltReady(false);
    SoundManager::GetInstance()->PlaySFX("Dante-Bow_UltSmall");
}

void PlayerSmallBowUlt::update(Player* player, float dt_) {
    time += dt_;
    //cout << "Player Idle State: " << time << " (total dt)\n";

    DrawableObject* collider = player->getBow()->getChainAttackObject(0);
    BowUltimateCollider* attackCollider = dynamic_cast<BowUltimateCollider*>(collider);

    switch (currentPhase) {
    case STARTUP:
        //do something
        //change phase

        if (time >= 0.75f) {
            currentPhase = ACTIVE;
            time = 0;
        }
        break;
    case ACTIVE:
        //do something
        //change phase
        if (time >= 0.083f) {
            currentPhase = RECOVERY;
            time = 0;
            attackCollider->resetHit();
            attackCollider->setEnable(true);
            if (player->getFacingRight()) {
                attackCollider->getTransform().setPosition(glm::vec3(player->getTransform().getPosition().x + attackCollider->getXOffset(), collider->getTransform().getPosition().y, collider->getTransform().getPosition().z));
            }
            else {
                attackCollider->getTransform().setPosition(glm::vec3(player->getTransform().getPosition().x - attackCollider->getXOffset(), collider->getTransform().getPosition().y, collider->getTransform().getPosition().z));
            }
            attackCollider->setTexture("../Resource/Texture/Dante/DanteBow/dante_smallUlt_effect.png", 1, 11, 0);
            attackCollider->getAnimationComponent()->setState("smallUlt");
            attackCollider->setDraw(true);
            collider->getColliderComponent()->setEnableCollision(true);
            //DrawableObject* newArrow = player->getBow()->arrowShot(100, 100, player, 75); //Change damage and ult gain percentage here
            //player->getLevel()->addObject(newArrow);
        }
        break;
    case RECOVERY:
        //do something
        //return to idle
        if (time >= 0.25f) {
            player->getStateMachine()->changeState(PlayerIdleState::getInstance(), player);
        }
        break;
    };

    /*if (time > 0.12f) {
        player->getAnimationComponent()->updateCurrentState();
        time = 0;
    }*/
}

void PlayerSmallBowUlt::exit(Player* player) {
    //cout << "Player exits Bow Small Ult state.\n";
    player->getBow()->setIsShooting(false);
}

//Bow Big Ultimate
void PlayerBigBowUlt::enter(Player* player) {
    //cout << "Player enters Bow Big Ult state.\n";
    player->setTexture("../Resource/Texture/Dante/DanteBow/dante_bigUlt_bow.png", 1, 18, 0);
    player->getAnimationComponent()->setState("bigUltBow");
    player->getAnimationComponent()->setLoop(false);
    currentPhase = STARTUP;
    time = 0.0f;
    player->getBow()->setIsShooting(true);
    player->getPhysicsComponent()->setVelocity(glm::vec2(0.0f, player->getPhysicsComponent()->getVelocity().y));

    player->getBow()->setBigUltReady(false);
    SoundManager::GetInstance()->PlaySFX("Dante-Bow_UltBig");
}

void PlayerBigBowUlt::update(Player* player, float dt_) {
    time += dt_;
    //cout << "Player Idle State: " << time << " (total dt)\n";

    DrawableObject* collider = player->getBow()->getChainAttackObject(1);
    BowUltimateCollider* attackCollider = dynamic_cast<BowUltimateCollider*>(collider);

    switch (currentPhase) {
    case STARTUP:
        //do something
        //change phase
        if (time >= 2.0f) {
            currentPhase = ACTIVE;
            time = 0;
        }
        break;
    case ACTIVE:
        //do something
        //change phase
        if (time >= 0.0f) {
            currentPhase = RECOVERY;
            time = 0;
            attackCollider->resetHit();
            attackCollider->setEnable(true);
            if (player->getFacingRight()) {
                attackCollider->getTransform().setPosition(glm::vec3(player->getTransform().getPosition().x + attackCollider->getXOffset(), collider->getTransform().getPosition().y, collider->getTransform().getPosition().z));
                cout << "Right: Player Pos " << player->getTransform().getPosition().x << " xOffset: " << attackCollider->getXOffset() << " Total: " << player->getTransform().getPosition().x + attackCollider->getXOffset() << endl;
            }
            else {
                attackCollider->getTransform().setPosition(glm::vec3(player->getTransform().getPosition().x - attackCollider->getXOffset(), collider->getTransform().getPosition().y, collider->getTransform().getPosition().z));
                cout << "Left: Player Pos " << player->getTransform().getPosition().x << " xOffset: " << attackCollider->getXOffset() << " Total: " << player->getTransform().getPosition().x - attackCollider->getXOffset() << endl;
            }
            attackCollider->setTexture("../Resource/Texture/Dante/DanteBow/dante_bigUlt_effect.png", 1, 15, 0);
            attackCollider->getAnimationComponent()->setState("bigUlt");
            attackCollider->setDraw(true);
            collider->getColliderComponent()->setEnableCollision(true);
            //DrawableObject* newArrow = player->getBow()->arrowShot(100, 100, player, 75); //Change damage and ult gain percentage here
            //player->getLevel()->addObject(newArrow);
        }
        break;
    case RECOVERY:
        //do something
        //return to idle
        if (time >= 0.25f) {
            player->getStateMachine()->changeState(PlayerIdleState::getInstance(), player);
        }
        break;
    };

    /*if (time > 0.12f) {
        player->getAnimationComponent()->updateCurrentState();
        time = 0;
    }*/
}

void PlayerBigBowUlt::exit(Player* player) {
    //cout << "Player exits Bow Big Ult state.\n";
    player->getBow()->setIsShooting(false);
    player->getAnimationComponent()->setLoop(true);
}