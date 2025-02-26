#include "PlayerShieldState.h"
#include "Player.h"
#include "Shield.h"
#include "Level.h"

PlayerLightShieldAttack1* PlayerLightShieldAttack1::instance = nullptr;
PlayerLightShieldAttack2* PlayerLightShieldAttack2::instance = nullptr;
PlayerShieldGuard* PlayerShieldGuard::instance = nullptr;
PlayerOffShield* PlayerOffShield::instance = nullptr;

//Light Shield Attack 1
void PlayerLightShieldAttack1::enter(Player* player) {
    cout << "Player enters Shield Light Attack 1 state.\n";
    player->getAnimationComponent()->setState("LightShieldAttack1");
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

    switch (currentPhase) {
    case STARTUP:
        //do something
        //change phase
        if (time >= 0.333f) {
            currentPhase = ACTIVE;
            time = 0;
        }
        break;
    case ACTIVE:
        //do something
        //change phase
        collider->setDrawCollider(true);
        collider->getColliderComponent()->setEnableCollision(true);
        if (time >= 0.333f) {
            currentPhase = RECOVERY;
            time = 0;

            collider->setDrawCollider(false);
            collider->getColliderComponent()->setEnableCollision(false);
            attackCollider->resetHit();
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
    cout << "Player exits Shield Light Attack 1 state.\n";
    player->getShield()->setCurrentChainAttack(0);
    player->getShield()->setInChainAttack(false); // no longer in chain attack
}

//Light Shield Attack 2
void PlayerLightShieldAttack2::enter(Player* player) {
    cout << "Player enters Shield Light Attack 2 state.\n";
    player->getAnimationComponent()->setState("LightShieldAttack2");
    currentPhase = STARTUP;
    time = 0.0f;
    player->getShield()->setCurrentChainAttack(2);
    player->getShield()->setInChainAttack(true); //Player is in chain attack
}

void PlayerLightShieldAttack2::update(Player* player, float dt_) {
    time += dt_;
    //cout << "Player Idle State: " << time << " (total dt)\n";

    DrawableObject* collider = player->getShield()->getChainAttackObject(1);
    PlayerAttackCollider* attackCollider = dynamic_cast<PlayerAttackCollider*>(collider);

    switch (currentPhase) {
    case STARTUP:
        //do something
        //change phase
        if (time >= 0.333f) {
            currentPhase = ACTIVE;
            time = 0;
        }
        break;
    case ACTIVE:
        //do something
        //change phase
        collider->setDrawCollider(true);
        collider->getColliderComponent()->setEnableCollision(true);

        if (time >= 0.333f) {
            currentPhase = RECOVERY;
            time = 0;

            collider->setDrawCollider(false);
            collider->getColliderComponent()->setEnableCollision(false);
            attackCollider->resetHit();
        }
        break;
    case RECOVERY:
        if (time >= 0.333f) { //time's up
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
    cout << "Player exits Shield Light Attack 2 state.\n";
}

//Shield Guard
void PlayerShieldGuard::enter(Player* player) {
    cout << "Player enters Shield Guard state.\n";
    player->getAnimationComponent()->setState("ShieldGuard");
    currentPhase = STARTUP;
    time = 0.0f;
    player->getShield()->setIsBlocking(true);
    player->getShield()->setIsHolding(true);
}

void PlayerShieldGuard::update(Player* player, float dt_) {
    time += dt_;
    //cout << "Player Idle State: " << time << " (total dt)\n";

    switch (currentPhase) {
    case STARTUP:
        //do something
        //change phase
        if (time >= 0.0f) {
            currentPhase = ACTIVE;
            time = 0;
            player->getShield()->setIsPerfect(true);
        }
        break;
    case ACTIVE:
        //do something
        //change phase

        if (time >= 1.0f) {
            time = 0;
            player->getShield()->setIsPerfect(false);
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
    cout << "Player exits Shield Guard state.\n";
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
    cout << "Player enters Off Shield state.\n";
    player->getAnimationComponent()->setState("OffShield");
    currentPhase = STARTUP;
    time = 0.0f;
}

void PlayerOffShield::update(Player* player, float dt_) {
    time += dt_;
    //cout << "Player Idle State: " << time << " (total dt)\n";

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

        if (time >= 0.083) {
            currentPhase = RECOVERY;
            time = 0;
        }
        break;
    case RECOVERY:

        if (time >= 0.083f) {
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
    cout << "Player exits Off Shield state.\n";
}