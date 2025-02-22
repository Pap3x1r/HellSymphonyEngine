#include "PlayerBowState.h"
#include "Player.h"
#include "Bow.h"
#include "Level.h"

PlayerLightBowAttack* PlayerLightBowAttack::instance = nullptr;
PlayerHeavyBowAttack* PlayerHeavyBowAttack::instance = nullptr;

//Bow Light Attack
void PlayerLightBowAttack::enter(Player* player) {
    cout << "Player enters Bow Light Attack state.\n";
    player->getAnimationComponent()->setState("LightBowAttack");
    currentPhase = STARTUP; //reset back to startup

    DrawableObject* newArrow = player->getBow()->arrowShot(10, 100, player, 25); //Change damage and ult gain percentage here
    player->getLevel()->addObject(newArrow);
}

void PlayerLightBowAttack::update(Player* player, float dt_) {
    time += dt_;
    //cout << "Player Idle State: " << time << " (total dt)\n";

    switch (currentPhase) {
    case STARTUP:
        //do something
        //change phase
        if (time >= 0.0f) { //this might need to change idk how to calculate dt to real time / frame lol
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
        //do something
        //return to idle
        if (time >= 0.0f) {
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
}

//Bow Heavy Attack
void PlayerHeavyBowAttack::enter(Player* player) {
    cout << "Player enters Bow Heavy Attack state.\n";
    player->getAnimationComponent()->setState("HeavyBowAttack");
    currentPhase = STARTUP;

    DrawableObject* newArrow = player->getBow()->arrowShot(100, 600, player, 75); //Change damage and ult gain percentage here
    player->getLevel()->addObject(newArrow);
}

void PlayerHeavyBowAttack::update(Player* player, float dt_) {
    time += dt_;
    //cout << "Player Idle State: " << time << " (total dt)\n";

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
        if (time >= 2.0f) {
            currentPhase = RECOVERY;
            time = 0;
        }
        break;
    case RECOVERY:
        //do something
        //return to idle
        if (time >= 2.0f) {
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
}