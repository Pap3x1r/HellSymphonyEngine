#include "PlayerShieldState.h"
#include "Player.h"
#include "Shield.h"
#include "Level.h"

PlayerLightShieldAttack1* PlayerLightShieldAttack1::instance = nullptr;
PlayerLightShieldAttack2* PlayerLightShieldAttack2::instance = nullptr;
PlayerShieldGuard* PlayerShieldGuard::instance = nullptr;
PlayerOffShield* PlayerOffShield::instance = nullptr;
PlayerSmallShieldUlt* PlayerSmallShieldUlt::instance = nullptr;
PlayerBigShieldUlt* PlayerBigShieldUlt::instance = nullptr;

//Light Shield Attack 1
void PlayerLightShieldAttack1::enter(Player* player) {
    //cout << "Player enters Shield Light Attack 1 state.\n";
    player->setTexture("../Resource/Texture/Dante/DanteShield/dante_lightAttack1_shield.png", 1, 16, 0);
    player->getAnimationComponent()->setState("lightAttack1Shield");
    currentPhase = STARTUP;
    time = 0.0f;
    player->getShield()->setCurrentChainAttack(1);
    player->getShield()->setInChainAttack(true); //Player is in chain attack

    player->getPhysicsComponent()->setVelocity(glm::vec2(0.0f, player->getPhysicsComponent()->getVelocity().y));
}

void PlayerLightShieldAttack1::update(Player* player, float dt_) {
    time += dt_;
    //cout << "Player Idle State: " << time << " (total dt)\n";

    /*list<DrawableObject*> attackList = player->getSword()->getChainAttackList();
    auto it = attackList.begin();
    advance(it, 0);*/

    DrawableObject* collider = player->getShield()->getChainAttackObject(0);
    PlayerAttackCollider* attackCollider = dynamic_cast<PlayerAttackCollider*>(collider);
    player->getPhysicsComponent()->setVelocity(glm::vec2(0.0f, player->getPhysicsComponent()->getVelocity().y));

    switch (currentPhase) {
    case STARTUP:

        //do something
        //change phase
        if (time >= 0.833f) {
            
            currentPhase = ACTIVE;
            time = 0;
            attackCollider->resetHit();
            collider->setDrawCollider(true);
            collider->getColliderComponent()->setEnableCollision(true);
            SoundManager::GetInstance()->PlaySFX("Dante-Shield_Attack-1");
        }
        break;
    case ACTIVE:
        //do something
        //change phase

        if (time >= 0.167f) {
            currentPhase = RECOVERY;
            time = 0;

            collider->setDrawCollider(false);
            collider->getColliderComponent()->setEnableCollision(false);
        }
        break;
    case RECOVERY:
        //do something
        //return to idle
        //allows 
        if (player->getShield()->getInputBuffer()) { //Ready for next attack
            player->getStateMachine()->changeState(PlayerLightShieldAttack2::getInstance(), player); //enter next phase
            player->getShield()->setInputBuffer(false); //remove input
            return;
        }

        if (time >= 0.333f) { //time's up
            player->getStateMachine()->changeState(PlayerIdleState::getInstance(), player);
            player->getShield()->setCurrentChainAttack(0);
            player->getShield()->setInChainAttack(false); // no longer in chain attack
        }
        break;
    };
}

void PlayerLightShieldAttack1::exit(Player* player) {
    //cout << "Player exits Shield Light Attack 1 state.\n";
    player->getShield()->setCurrentChainAttack(0);
    player->getShield()->setInChainAttack(false); // no longer in chain attack
}

//Light Shield Attack 2
void PlayerLightShieldAttack2::enter(Player* player) {
    //cout << "Player enters Shield Light Attack 2 state.\n";
    player->setTexture("../Resource/Texture/Dante/DanteShield/dante_lightAttack2_shield.png", 1, 11, 0);
    player->getAnimationComponent()->setState("lightAttack2Shield");
    currentPhase = STARTUP;
    time = 0.0f;
    player->getShield()->setCurrentChainAttack(2);
    player->getShield()->setInChainAttack(true); //Player is in chain attack
    player->getPhysicsComponent()->setVelocity(glm::vec2(0.0f, player->getPhysicsComponent()->getVelocity().y));
}

void PlayerLightShieldAttack2::update(Player* player, float dt_) {
    time += dt_;
    //cout << "Player Idle State: " << time << " (total dt)\n";

    DrawableObject* collider = player->getShield()->getChainAttackObject(1);
    PlayerAttackCollider* attackCollider = dynamic_cast<PlayerAttackCollider*>(collider);
    player->getPhysicsComponent()->setVelocity(glm::vec2(0.0f, player->getPhysicsComponent()->getVelocity().y));

    switch (currentPhase) {
    case STARTUP:
        //do something
        //change phase
        if (time >= 0.25f) {
            currentPhase = ACTIVE;
            time = 0;
            attackCollider->resetHit();
            collider->setDrawCollider(true);
            collider->getColliderComponent()->setEnableCollision(true);
            SoundManager::GetInstance()->PlaySFX("Dante-Shield_Attack-2");
        }
        break;
    case ACTIVE:
        //do something
        //change phase


        if (time >= 0.167f) {
            currentPhase = RECOVERY;
            time = 0;

            collider->setDrawCollider(false);
            collider->getColliderComponent()->setEnableCollision(false);
        }
        break;
    case RECOVERY:
        if (time >= 0.5f) { //time's up
            player->getStateMachine()->changeState(PlayerIdleState::getInstance(), player);
            player->getShield()->setCurrentChainAttack(0);
            player->getShield()->setInChainAttack(false); // no longer in chain attack
        }
        break;
    };

    /*if (time > 0.12f) {
        player->getAnimationComponent()->updateCurrentState();
        time = 0;
    }*/
}

void PlayerLightShieldAttack2::exit(Player* player) {
    //cout << "Player exits Shield Light Attack 2 state.\n";
    player->getShield()->setInChainAttack(false);
    player->getShield()->setCurrentChainAttack(0);
}

//Shield Guard
void PlayerShieldGuard::enter(Player* player) {
    //cout << "Player enters Shield Guard state.\n";
    player->getPhysicsComponent()->setVelocity(glm::vec2(0.0f, 0.0f));
    player->setTexture("../Resource/Texture/Dante/DanteShield/dante_holding_shield.png", 1, 3, 0);
    player->getAnimationComponent()->setState("holdShield");
    player->getAnimationComponent()->setLoop(false);
    currentPhase = STARTUP;
    time = 0.0f;
    player->getShield()->setIsBlocking(true);
    player->getShield()->setIsHolding(true);
}

void PlayerShieldGuard::update(Player* player, float dt_) {
    time += dt_;
    //cout << "Player Idle State: " << time << " (total dt)\n";
    player->getPhysicsComponent()->setVelocity(glm::vec2(0.0f, player->getPhysicsComponent()->getVelocity().y));
    switch (currentPhase) {
    case STARTUP:
        //do something
        //change phase
        if (time >= 0.083f) {
            currentPhase = ACTIVE;
            time = 0;
            player->getShield()->setIsPerfect(true);
            //cout << "perfect" << endl;
        }
        break;
    case ACTIVE:
        //do something
        //change phase

        if (time >= 0.1f) {
            time = 0;
            player->getShield()->setIsPerfect(false);
            //cout << "not perfect" << endl;
        }
        break;
    }

    //Stay on guard if player keep holding right mouse button


    //If it hits in time = perfect block (no damage taken)


    /*if (time > 0.12f) {
        player->getAnimationComponent()->updateCurrentState();
        time = 0;
    }*/
}

void PlayerShieldGuard::exit(Player* player) {
    //cout << "Player exits Shield Guard state.\n";
    player->getAnimationComponent()->setLoop(true);
    player->getShield()->setIsBlocking(false);
}

void PlayerShieldGuard::changeState(int phase) {
    switch (phase) {
    case 0:
        currentPhase = STARTUP;
        break;
    case 1:
        currentPhase = ACTIVE;
        break;
    case 2:
        currentPhase = RECOVERY;
        break;
    }
}

//Player off shield
void PlayerOffShield::enter(Player* player) {
    //cout << "Player enters Off Shield state.\n";
    player->setTexture("../Resource/Texture/Dante/DanteShield/dante_off_shield.png", 1, 3, 0);
    player->getAnimationComponent()->setState("offShield");
    player->getAnimationComponent()->setLoop(false);
    currentPhase = STARTUP;
    time = 0.0f;
    
}

void PlayerOffShield::update(Player* player, float dt_) {
    time += dt_;
    //cout << "Player Idle State: " << time << " (total dt)\n";
    player->getPhysicsComponent()->setVelocity(glm::vec2(0.0f, player->getPhysicsComponent()->getVelocity().y));
    switch (currentPhase) {
    case STARTUP:
        //do something
        //change phase
        if (time >= 0.0f) {
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
        }
        break;
    case RECOVERY:

        if (time >= 0.25f) {
            time = 0;
            player->getShield()->setCurrentChainAttack(0);
            player->getShield()->setInChainAttack(false); // no longer in chain attack
            player->getShield()->setIsHolding(false);
            player->getStateMachine()->changeState(PlayerIdleState::getInstance(), player); //from off shield to idle
        }
    }

    //Stay on guard if player keep holding right mouse button


    //If it hits in time = perfect block (no damage taken)


    /*if (time > 0.12f) {
        player->getAnimationComponent()->updateCurrentState();
        time = 0;
    }*/
}

void PlayerOffShield::exit(Player* player) {
    player->getAnimationComponent()->setLoop(true);
    //cout << "Player exits Off Shield state.\n";
    player->getShield()->setIsBlocking(false);
    player->getShield()->setIsHolding(false);
}

//Small Shield Ult
void PlayerSmallShieldUlt::enter(Player* player) {
    //cout << "Player enters Shield Small Ult state.\n";
    player->setTexture("../Resource/Texture/Dante/DanteShield/dante_smallUlt_shield.png", 1, 11, 0);
    player->getAnimationComponent()->setState("smallUltShield");
    currentPhase = STARTUP;
    time = 0.0f;
    player->getShield()->setInChainAttack(true); //Player is in chain attack
    player->setInvincibleFloat(1.0f);

    player->getShield()->setSmallUltReady(false);
}

void PlayerSmallShieldUlt::update(Player* player, float dt_) {
    time += dt_;
    //cout << "Player Idle State: " << time << " (total dt)\n";

    DrawableObject* collider = player->getShield()->getChainAttackObject(2);
    PlayerAttackCollider* attackCollider = dynamic_cast<PlayerAttackCollider*>(collider);
    player->getPhysicsComponent()->setVelocity(glm::vec2(0.0f, player->getPhysicsComponent()->getVelocity().y));

    switch (currentPhase) {
    case STARTUP:
        //do something
        //change phase
        if (time >= 0.25f) {
            currentPhase = ACTIVE;
            time = 0;
            attackCollider->resetHit();
            collider->setDrawCollider(true);
            collider->getColliderComponent()->setEnableCollision(true); //Enable once after startup
            attackCollider->setTexture("../Resource/Texture/Dante/DanteShield/dante_shield_smallUlt_explosion.png", 1, 10, 0);
            attackCollider->getAnimationComponent()->setState("explosion");
            attackCollider->setDraw(true);
            SoundManager::GetInstance()->PlaySFX("Dante-Shield_UltSmall");
        }
        break;
    case ACTIVE:
        //do something
        //change phase
        

        if (time >= 0.167f) {
            currentPhase = RECOVERY;
            time = 0;

            collider->setDrawCollider(false); //Close when active end
            collider->getColliderComponent()->setEnableCollision(false);
        }
        break;
    case RECOVERY:
        if (time >= 0.5f) { //time's up
            player->getShield()->setInChainAttack(false); // no longer in chain attack
            player->getStateMachine()->changeState(PlayerIdleState::getInstance(), player);
        }
        break;
    };

    /*if (time > 0.12f) {
        player->getAnimationComponent()->updateCurrentState();
        time = 0;
    }*/
}

void PlayerSmallShieldUlt::exit(Player* player) {
    //cout << "Player exits Shield Small Ult state.\n";
    player->getShield()->setSmallUltReady(true);

}

//Shield Big Ult
void PlayerBigShieldUlt::enter(Player* player) {
    //cout << "Player enters Shield Big Ult state.\n";
    player->setTexture("../Resource/Texture/Dante/DanteShield/dante_bigUlt_shield.png", 1, 24, 0);
    player->getAnimationComponent()->setState("bigUltShield");
    player->getAnimationComponent()->setLoop(false);
    currentPhase = STARTUP;
    time = 0.0f;
    player->getShield()->setInChainAttack(true); //Player is in chain attack
    player->setInvincibleFloat(2.0f);

    player->getShield()->setBigUltReady(false);
    SoundManager::GetInstance()->PlaySFX("Dante-Shield_UltBig");
}

void PlayerBigShieldUlt::update(Player* player, float dt_) {
    time += dt_;
    //cout << "Player Idle State: " << time << " (total dt)\n";

    DrawableObject* collider = player->getShield()->getChainAttackObject(3);
    PlayerAttackCollider* attackCollider = dynamic_cast<PlayerAttackCollider*>(collider);
    player->getPhysicsComponent()->setVelocity(glm::vec2(0.0f, player->getPhysicsComponent()->getVelocity().y));

    switch (currentPhase) {
    case STARTUP:
        //do something
        //change phase
        if (time >= 1.7f) {
            currentPhase = ACTIVE;
            time = 0;
            attackCollider->resetHit();
            collider->setDrawCollider(true);
            collider->getColliderComponent()->setEnableCollision(true);
            attackCollider->setTexture("../Resource/Texture/Dante/DanteShield/dante_shield_bigUlt_explosion.png", 1, 12, 0);
            attackCollider->getAnimationComponent()->setState("explosion");
            attackCollider->setDraw(true);
        }
        break;
    case ACTIVE:
        //do something
        //change phase

        if (time >= 0.167f) {
            currentPhase = RECOVERY;
            time = 0;

            collider->setDrawCollider(false);
            collider->getColliderComponent()->setEnableCollision(false);
        }
        break;
    case RECOVERY:
        if (time >= 0.0f) { //time's up
            player->getShield()->setInChainAttack(false); // no longer in chain attack
            player->getStateMachine()->changeState(PlayerIdleState::getInstance(), player);
        }
        break;
    };

    /*if (time > 0.12f) {
        player->getAnimationComponent()->updateCurrentState();
        time = 0;
    }*/
}

void PlayerBigShieldUlt::exit(Player* player) {
    //cout << "Player exits Shield Big Ult state.\n";
    player->getShield()->setBigUltReady(true);
    player->getAnimationComponent()->setLoop(false);
}