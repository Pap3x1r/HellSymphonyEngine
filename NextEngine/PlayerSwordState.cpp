#include "PlayerSwordState.h"
#include "Player.h"
#include "Sword.h"
#include "Level.h"

PlayerLightSwordAttack1* PlayerLightSwordAttack1::instance = nullptr;
PlayerLightSwordAttack2* PlayerLightSwordAttack2::instance = nullptr;
PlayerLightSwordAttack3* PlayerLightSwordAttack3::instance = nullptr;
PlayerHeavySwordAttack* PlayerHeavySwordAttack::instance = nullptr;

//Light Sword Attack 1
void PlayerLightSwordAttack1::enter(Player* player) {
    cout << "Player enters Sword Light Attack 1 state.\n";
    player->setTexture("../Resource/Texture/Dante/DanteSword/dante_lightAttack1_sword.png", 1, 6, 0);
    player->getAnimationComponent()->setState("lightAttack1Sword");
    currentPhase = STARTUP;
    time = 0.0f;
    player->getSword()->setCurrentChainAttack(1);
    player->getSword()->setInChainAttack(true); //Player is in chain attack

    player->getPhysicsComponent()->setVelocity(glm::vec2(0.0f, player->getPhysicsComponent()->getVelocity().y));
}

void PlayerLightSwordAttack1::update(Player* player, float dt_) {
    time += dt_;
    //cout << "Player Idle State: " << time << " (total dt)\n";

    /*list<DrawableObject*> attackList = player->getSword()->getChainAttackList();
    auto it = attackList.begin();
    advance(it, 0);*/

    DrawableObject* collider = player->getSword()->getChainAttackObject(0);
    PlayerAttackCollider* attackCollider = dynamic_cast<PlayerAttackCollider*>(collider);

    switch (currentPhase) {
    case STARTUP:
        //do something
        //change phase
        if (time >= 0.167f) { //4 frames
            currentPhase = ACTIVE;
            time = 0;
        }
        break;
    case ACTIVE:
        //do something
        //change phase
        collider->setDrawCollider(true);
        collider->getColliderComponent()->setEnableCollision(true);

        if (time >= 0.25f) {
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
        
        if (player->getSword()->getInputBuffer()) { //Ready for next attack
            player->getStateMachine()->changeState(PlayerLightSwordAttack2::getInstance(), player); //enter next phase
            player->getSword()->setInputBuffer(false); //remove input
            return;
        }

        if (time >= 0.083f) { //time's up
            player->getStateMachine()->changeState(PlayerIdleState::getInstance(), player);
            player->getSword()->setCurrentChainAttack(0);
            player->getSword()->setInChainAttack(false); // no longer in chain attack
        }
        break;
    };
}

void PlayerLightSwordAttack1::exit(Player* player) {
    cout << "Player exits Sword Light Attack 1 state.\n";
}

//Light Sword Attack 2
void PlayerLightSwordAttack2::enter(Player* player) {
    cout << "Player enters Sword Light Attack 2 state.\n";
    player->setTexture("../Resource/Texture/Dante/DanteSword/dante_lightAttack2_sword.png", 1, 4, 0);
    player->getAnimationComponent()->setState("lightAttack2Sword");
    currentPhase = STARTUP;
    time = 0.0f;
    player->getSword()->setCurrentChainAttack(2);
    player->getSword()->setInChainAttack(true); //Player is in chain attack
}

void PlayerLightSwordAttack2::update(Player* player, float dt_) {
    time += dt_;
    //cout << "Player Idle State: " << time << " (total dt)\n";

    DrawableObject* collider = player->getSword()->getChainAttackObject(1);
    PlayerAttackCollider* attackCollider = dynamic_cast<PlayerAttackCollider*>(collider);

    switch (currentPhase) {
    case STARTUP:
        //do something
        //change phase
        if (time >= 0.167f) {
            currentPhase = ACTIVE;
            time = 0;
        }
        break;
    case ACTIVE:
        //do something
        //change phase
        collider->setDrawCollider(true);
        collider->getColliderComponent()->setEnableCollision(true);

        if (time >= 0.167f) {
            currentPhase = RECOVERY;
            time = 0;

            collider->setDrawCollider(false);
            collider->getColliderComponent()->setEnableCollision(false);
            attackCollider->resetHit();
        }
        break;
    case RECOVERY:
        if (player->getSword()->getInputBuffer()) { //Ready for next attack
            player->getStateMachine()->changeState(PlayerLightSwordAttack3::getInstance(), player); //enter next phase
            player->getSword()->setInputBuffer(false); //remove input
            return;
        }

        if (time >= 0.0f) { //time's up
            player->getStateMachine()->changeState(PlayerIdleState::getInstance(), player);
            player->getSword()->setCurrentChainAttack(0);
            player->getSword()->setInChainAttack(false); // no longer in chain attack
        }
        break;
    };

    /*if (time > 0.12f) {
        player->getAnimationComponent()->updateCurrentState();
        time = 0;
    }*/
}

void PlayerLightSwordAttack2::exit(Player* player) {
    cout << "Player exits Sword Light Attack 2 state.\n";
}

//Light Sword Attack 3
void PlayerLightSwordAttack3::enter(Player* player) {
    cout << "Player enters Sword Light Attack 3 state.\n";
    player->setTexture("../Resource/Texture/Dante/DanteSword/dante_lightAttack3_sword.png", 1, 4, 0);
    player->getAnimationComponent()->setState("lightAttack3Sword");
    currentPhase = STARTUP;
    time = 0.0f;
    player->getSword()->setCurrentChainAttack(3);
    player->getSword()->setInChainAttack(true); //Player is in chain attack
}

void PlayerLightSwordAttack3::update(Player* player, float dt_) {
    time += dt_;
    //cout << "Player Idle State: " << time << " (total dt)\n";
    DrawableObject* collider = player->getSword()->getChainAttackObject(2);
    PlayerAttackCollider* attackCollider = dynamic_cast<PlayerAttackCollider*>(collider);

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

        collider->setDrawCollider(true);
        collider->getColliderComponent()->setEnableCollision(true);

        if (time >= 0.167f) {
            currentPhase = RECOVERY;
            time = 0;
            collider->setDrawCollider(false);
            collider->getColliderComponent()->setEnableCollision(false);
            attackCollider->resetHit();
        }
        break;
    case RECOVERY:

        if (time >= 0.167f) { //time's up
            player->getStateMachine()->changeState(PlayerIdleState::getInstance(), player);
            player->getSword()->setCurrentChainAttack(0);
            player->getSword()->setInChainAttack(false); // no longer in chain attack
        }
        break;
    };

    /*if (time > 0.12f) {
        player->getAnimationComponent()->updateCurrentState();
        time = 0;
    }*/
}

void PlayerLightSwordAttack3::exit(Player* player) {
    cout << "Player exits Sword Light Attack 3 state.\n";
}

//Heavy Sword Attack
void PlayerHeavySwordAttack::enter(Player* player) {
    cout << "Player enters Sword Heavy Attack state.\n";
    player->getAnimationComponent()->setState("HeavySwordAttack");
    currentPhase = STARTUP;
}

void PlayerHeavySwordAttack::update(Player* player, float dt_) {
    time += dt_;
    //cout << "Player Idle State: " << time << " (total dt)\n";

    DrawableObject* collider = player->getSword()->getChainAttackObject(3);
    PlayerAttackCollider* attackCollider = dynamic_cast<PlayerAttackCollider*>(collider);

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

        collider->setDrawCollider(true);
        collider->getColliderComponent()->setEnableCollision(true);

        if (time >= 1.0f) {
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
        if (time >= 0.166f) {
            player->getStateMachine()->changeState(PlayerIdleState::getInstance(), player);
        }
        break;
    };

    /*if (time > 0.12f) {
        player->getAnimationComponent()->updateCurrentState();
        time = 0;
    }*/
}

void PlayerHeavySwordAttack::exit(Player* player) {
    cout << "Player exits Sword Heavy Attack state.\n";
}