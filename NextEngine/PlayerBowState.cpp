#include "PlayerBowState.h"
#include "Player.h"
#include "Bow.h"
#include "Level.h"

PlayerLightBowAttack* PlayerLightBowAttack::instance = nullptr;
PlayerHeavyBowAttack* PlayerHeavyBowAttack::instance = nullptr;

//Bow Light Attack
void PlayerLightBowAttack::enter(Player* player) {
    cout << "Player enters Bow Light Attack state.\n";
    player->setTexture("../Resource/Texture/Dante/DanteBow/dante_lightAttack_bow.png", 1, 8, 0); //set new texture ("path", row, column)
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

            DrawableObject* newArrow = player->getBow()->arrowShot(10, 100, player, 25); //Change damage and ult gain percentage here
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
    cout << "Player exits Bow Light Attack state.\n";
    player->getBow()->setIsShooting(false);
}

//Bow Heavy Attack
void PlayerHeavyBowAttack::enter(Player* player) {
    cout << "Player enters Bow Heavy Attack state.\n";
    player->setTexture("../Resource/Texture/Dante/DanteBow/dante_heavyAttack_bow.png", 1, 16, 0);
    player->getAnimationComponent()->setState("heavyAttackBow");
    currentPhase = STARTUP;
    time = 0.0f;
    player->getBow()->setIsShooting(true);
    player->getPhysicsComponent()->setVelocity(glm::vec2(0.0f, player->getPhysicsComponent()->getVelocity().y));
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
            DrawableObject* newArrow = player->getBow()->arrowShot(100, 100, player, 75); //Change damage and ult gain percentage here
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
    cout << "Player exits Bow Heavy Attack state.\n";
    player->getBow()->setIsShooting(false);
}